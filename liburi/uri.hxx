#ifndef liburi__uri_hxx_
#define liburi__uri_hxx_

#include <liburi/optional.hxx>

#include <string>

namespace uri {

class uri;

optional< uri >
try_parse_uri(std::string const& str);

class uri {
public:
  uri();

  uri(std::string scheme, std::string host, std::string path);

  uri(std::string scheme, std::string host, std::string port, std::string path);

  uri(std::string scheme,
      std::string host,
      std::string port,
      std::string path,
      std::string query);

  uri(std::string scheme,
      std::string host,
      std::string port,
      std::string path,
      std::string query,
      std::string fragment);

  uri(std::string scheme,
      std::string userinfo,
      std::string host,
      std::string port,
      std::string path,
      std::string query,
      std::string fragment);

  uri(optional< std::string > scheme,
      optional< std::string > userinfo,
      optional< std::string > host,
      optional< std::string > port,
      std::string path,
      optional< std::string > query,
      optional< std::string > fragment);

  optional< std::string > const&
  scheme() const;

  std::string
  scheme_str() const;

  optional< std::string > const&
  userinfo() const;

  std::string
  userinfo_str() const;

  optional< std::string > const&
  host() const;

  std::string
  host_str() const;

  optional< std::string > const&
  port() const;

  std::string
  port_str() const;

  std::string
  path_str() const;

  optional< std::string > const&
  query() const;

  std::string
  query_str() const;

  optional< std::string > const&
  fragment() const;

  std::string
  fragment_str() const;

  static optional< uri >
  try_parse(std::string const& str)
  {
    return try_parse_uri(str);
  }

private:
  optional< std::string > scheme_;
  optional< std::string > userinfo_;
  optional< std::string > host_;
  optional< std::string > port_;
  std::string path_;
  optional< std::string > query_;
  optional< std::string > fragment_;
};

bool
operator==(uri const& lhs, uri const& rhs);

bool
operator!=(uri const& lhs, uri const& rhs);

} // namespace uri

#include <liburi/uri.ixx>

#endif
