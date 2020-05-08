namespace uri {

inline uri::uri()
{}

inline uri::uri(std::string scheme, std::string host, std::string path)
  : scheme_{ std::move(scheme) },
    host_{ std::move(host) },
    path_{ std::move(path) }
{}

inline uri::uri(std::string scheme,
                std::string host,
                std::string port,
                std::string path)
  : scheme_{ std::move(scheme) },
    host_{ std::move(host) },
    port_{ std::move(port) },
    path_{ std::move(path) }
{}

inline uri::uri(std::string scheme,
                std::string host,
                std::string port,
                std::string path,
                std::string query)
  : scheme_{ std::move(scheme) },
    host_{ std::move(host) },
    port_{ std::move(port) },
    path_{ std::move(path) },
    query_{ std::move(query) }
{}

inline uri::uri(std::string scheme,
                std::string host,
                std::string port,
                std::string path,
                std::string query,
                std::string fragment)
  : scheme_{ std::move(scheme) },
    host_{ std::move(host) },
    port_{ std::move(port) },
    path_{ std::move(path) },
    query_{ std::move(query) },
    fragment_{ std::move(fragment) }
{}

inline uri::uri(std::string scheme,
                std::string userinfo,
                std::string host,
                std::string port,
                std::string path,
                std::string query,
                std::string fragment)
  : scheme_{ std::move(scheme) },
    userinfo_{ std::move(userinfo) },
    host_{ std::move(host) },
    port_{ std::move(port) },
    path_{ std::move(path) },
    query_{ std::move(query) },
    fragment_{ std::move(fragment) }
{}

inline uri::uri(optional< std::string > scheme,
                optional< std::string > userinfo,
                optional< std::string > host,
                optional< std::string > port,
                std::string path,
                optional< std::string > query,
                optional< std::string > fragment)
  : scheme_{ std::move(scheme) },
    userinfo_{ std::move(userinfo) },
    host_{ std::move(host) },
    port_{ std::move(port) },
    path_{ std::move(path) },
    query_{ std::move(query) },
    fragment_{ std::move(fragment) }
{}

inline optional< std::string > const&
uri::scheme() const
{
  return scheme_;
}

inline std::string
uri::scheme_str() const
{
  return scheme().value_or(std::string{});
}

inline optional< std::string > const&
uri::userinfo() const
{
  return userinfo_;
}

inline std::string
uri::userinfo_str() const
{
  return userinfo().value_or(std::string{});
}

inline optional< std::string > const&
uri::host() const
{
  return host_;
}

inline std::string
uri::host_str() const
{
  return host().value_or(std::string{});
}

inline optional< std::string > const&
uri::port() const
{
  return port_;
}

inline std::string
uri::port_str() const
{
  return port().value_or(std::string{});
}

inline std::string
uri::path_str() const
{
  return path_;
}

inline optional< std::string > const&
uri::query() const
{
  return query_;
}

inline std::string
uri::query_str() const
{
  return query().value_or(std::string{});
}

inline optional< std::string > const&
uri::fragment() const
{
  return fragment_;
}

inline std::string
uri::fragment_str() const
{
  return fragment().value_or(std::string{});
}

} // namespace uri
