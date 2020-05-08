#include <libunittest/unittest.hxx>

#include <liburi/uri.hxx>

DEFINE_TEST("uri()")
{
  uri::uri uri{};

  TEST_FALSE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_FALSE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_TRUE(uri.path_str().empty());
}

DEFINE_TEST("uri(scheme, host, path)")
{
  uri::uri uri{ "http", "localhost", "/index.html" };

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "http");
  TEST_EQUAL(uri.host_str(), "localhost");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("uri(scheme, host, port, path)")
{
  uri::uri uri{ "https", "localhost", "8443", "/index.html" };

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "localhost");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("uri(scheme, host, port, path, query)")
{
  uri::uri uri{ "https", "localhost", "8443", "/search", "q=hamsters" };

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "localhost");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
}

DEFINE_TEST("uri(scheme, host, port, path, query, fragment)")
{
  uri::uri uri{
    "https", "localhost", "8443", "/search", "q=hamsters", "results"
  };

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_TRUE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "localhost");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
  TEST_EQUAL(uri.fragment_str(), "results");
}

DEFINE_TEST("uri(scheme, userinfo, host, port, path, query, fragment)")
{
  uri::uri uri{ std::string{ "https" },     std::string{ "admin:qwerty" },
                std::string{ "localhost" }, std::string{ "8443" },
                std::string{ "/search" },   std::string{ "q=hamsters" },
                std::string{ "results" } };

  TEST_TRUE((bool)uri.scheme());
  TEST_TRUE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_TRUE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.userinfo_str(), "admin:qwerty");
  TEST_EQUAL(uri.host_str(), "localhost");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
  TEST_EQUAL(uri.fragment_str(), "results");
}
