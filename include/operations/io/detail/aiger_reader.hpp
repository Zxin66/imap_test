// ***************************************************************************************
// Copyright (c) 2023-2025 Peng Cheng Laboratory
// Copyright (c) 2023-2025 Shanghai Anlogic Infotech Co.,Ltd.
// Copyright (c) 2023-2025 Peking University
//
// iMAP-FPGA is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
// http://license.coscl.org.cn/MulanPSL2
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//
// See the Mulan PSL v2 for more details.
// ***************************************************************************************

#pragma once

#include "network/aig_network.hpp"
#include "utils/traits.hpp"
#include <lorina/aiger.hpp>

iFPGA_NAMESPACE_HEADER_START

template<typename Ntk, typename StorageContainerMap = std::unordered_map<signal<Ntk>, std::vector<std::string>>, typename StorageContainerReverseMap = std::unordered_map<std::string, signal<Ntk>>>
class NameMap
{
public:
  using signal = typename Ntk::signal;

public:
  NameMap() = default;

  void insert( signal const& s, std::string const& name )
  {
    if(name.empty()) return;
    /* update direct map */
    auto const it = _names.find( s );
    if ( it == _names.end() )
    {
      _names[s] = {name};
    }
    else
    {
      it->second.push_back( name );
    }

    /* update reverse map */
    auto const rev_it = _rev_names.find( name );
    if ( rev_it != _rev_names.end() )
    {
      std::cout << "[w] signal name `" << name << "` is used twice" << std::endl;
    }
    _rev_names.insert( std::make_pair( name, s ) );
  }

  std::vector<std::string> operator[]( signal const& s )
  {
    return _names[s];
  }

  std::vector<std::string> operator[]( signal const& s ) const
  {
    return _names.at( s );
  }

  std::vector<std::string> get_name( signal const& s ) const
  {
    return _names.at( s );
  }

  bool has_name( signal const& s, std::string const& name ) const
  {
    auto const it = _names.find( s );
    if ( it == _names.end() )
    {
      return false;
    }
    return ( std::find( it->second.begin(), it->second.end(), name ) != it->second.end() );
  }

  StorageContainerReverseMap get_name_to_signal_mapping() const
  {
    return _rev_names;
  }

protected:
  StorageContainerMap _names;
  StorageContainerReverseMap _rev_names;
}; // NameMap

/*! \brief Lorina reader callback for Aiger files.
 *
 * **Required network functions:**
 * - `create_pi`
 * - `create_po`
 * - `get_constant`
 * - `create_not`
 * - `create_and`
 *
 * **Optional network functions to support sequential networks:**
 * - `create_ri`
 * - `create_ro`
 *
   \verbatim embed:rst

   Example

   .. code-block:: c++

      aig_network aig;
      lorina::read_aiger( "file.aig", aiger_reader( aig ) );

      mig_network mig;
      lorina::read_aiger( "file.aig", aiger_reader( mig ) );
   \endverbatim
 */
template<typename Ntk>
class aiger_reader : public lorina::aiger_reader
{
public:
  explicit aiger_reader( Ntk& ntk, NameMap<Ntk>* names = nullptr ) : _ntk( ntk ), _names( names )
  {
    static_assert( is_network_type_v<Ntk>, "Ntk is not a network type" );
    static_assert( has_create_pi_v<Ntk>, "Ntk does not implement the create_pi function" );
    static_assert( has_create_po_v<Ntk>, "Ntk does not implement the create_po function" );
    static_assert( has_get_constant_v<Ntk>, "Ntk does not implement the get_constant function" );
    static_assert( has_create_not_v<Ntk>, "Ntk does not implement the create_not function" );
    static_assert( has_create_and_v<Ntk>, "Ntk does not implement the create_and function" );
  }

  ~aiger_reader()
  {
    for ( auto out : outputs )
    {
      auto const lit = std::get<0>( out );
      auto signal = signals[lit >> 1];
      if ( lit & 1 )
      {
        signal = _ntk.create_not( signal );
      }
      if ( _names )
        _names->insert( signal, std::get<1>( out ) );
      _ntk.create_po( signal );
    }

    if constexpr ( has_create_ri_v<Ntk> && has_create_ro_v<Ntk> )
    {
      for ( auto latch : latches )
      {
        auto const lit = std::get<0>( latch );
        auto const reset = std::get<1>( latch );

        auto signal = signals[lit >> 1];
        if ( lit & 1 )
        {
          signal = _ntk.create_not( signal );
        }

        if ( _names )
          _names->insert( signal, std::get<2>( latch ) + "_next" );
        _ntk.create_ri( signal, reset );
      }
    }
  }

  void on_header( uint64_t, uint64_t num_inputs, uint64_t num_latches, uint64_t, uint64_t ) const override
  {
    (void)num_latches;
    if constexpr ( !has_create_ri_v<Ntk> || !has_create_ro_v<Ntk> )
    {
      assert( num_latches == 0 && "network type does not support the creation of latches" );
    }

    _num_inputs = static_cast<uint32_t>( num_inputs );

    /* constant */
    signals.push_back( _ntk.get_constant( false ) );

    /* create primary inputs (pi) */
    for ( auto i = 0u; i < num_inputs; ++i )
    {
      signals.push_back( _ntk.create_pi() );
    }

    if constexpr ( has_create_ri_v<Ntk> && has_create_ro_v<Ntk> )
    {
      /* create latch outputs (ro) */
      for ( auto i = 0u; i < num_latches; ++i )
      {
        signals.push_back( _ntk.create_ro() );
      }
    }
  }

  void on_input_name( unsigned index, const std::string& name ) const override
  {
    if ( _names )
    {
      _names->insert( signals[1 + index], name );
    }
  }

  void on_output_name( unsigned index, const std::string& name ) const override
  {
    std::get<1>( outputs[index] ) = name;
  }

  void on_latch_name( unsigned index, const std::string& name ) const override
  {
    if constexpr ( has_create_ri_v<Ntk> && has_create_ro_v<Ntk> )
    {
      if ( _names )
      {
        _names->insert( signals[1 + _num_inputs + index], name );
      }
      std::get<2>( latches[index] ) = name;
    }
  }

  void on_and( unsigned index, unsigned left_lit, unsigned right_lit ) const override
  {
    (void)index;
    assert( signals.size() == index );

    auto left = signals[left_lit >> 1];
    if ( left_lit & 1 )
    {
      left = _ntk.create_not( left );
    }

    auto right = signals[right_lit >> 1];
    if ( right_lit & 1 )
    {
      right = _ntk.create_not( right );
    }

    signals.push_back( _ntk.create_and( left, right ) );
  }

  void on_latch( unsigned index, unsigned next, latch_init_value reset ) const override
  {
    if constexpr ( has_create_ri_v<Ntk> && has_create_ro_v<Ntk> )
    {
      (void)index;
      int8_t r = reset == latch_init_value::NONDETERMINISTIC ? -1 : ( reset == latch_init_value::ONE ? 1 : 0 );
      latches.push_back( std::make_tuple( next, r, "" ) );
    }
  }

  void on_output( unsigned index, unsigned lit ) const override
  {
    (void)index;
    assert( index == outputs.size() );
    outputs.emplace_back( lit, "" );
  }

private:
  Ntk& _ntk;

  mutable uint32_t _num_inputs = 0;
  mutable std::vector<std::tuple<unsigned, std::string>> outputs;
  mutable std::vector<typename Ntk::signal> signals;
  mutable std::vector<std::tuple<unsigned, int8_t, std::string>> latches;
  mutable NameMap<Ntk>* _names;
};

iFPGA_NAMESPACE_HEADER_END