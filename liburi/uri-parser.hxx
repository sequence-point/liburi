#ifndef liburi__uri_parser_hxx_
#define liburi__uri_parser_hxx_

#include <liburi/grammar.hxx>
#include <liburi/optional.hxx>
#include <liburi/uri.hxx>

#include <cassert>
#include <string>

namespace uri {

template< typename Iterator >
optional< uri >
try_parse_uri(Iterator first, Iterator last);

optional< uri >
try_parse_uri(std::string const& str);

} // namespace uri

#include <liburi/uri-parser.ixx>
#include <liburi/uri-parser.txx>

#endif
