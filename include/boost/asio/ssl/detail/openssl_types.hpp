//
// ssl/detail/openssl_types.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP
#define BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#if defined(BOOST_ASIO_USE_WOLFSSL)
# include <wolfssl/options.h>
#endif // defined(BOOST_ASIO_USE_WOLFSSL)
#include $1
#include $1
#if !defined(OPENSSL_NO_ENGINE)
# include $1
#endif // !defined(OPENSSL_NO_ENGINE)
#include $1
#include $1
#include $1
#include $1

#endif // BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP