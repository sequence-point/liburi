#include <libunittest/unittest.hxx>

#include <liburi/uri-parser.hxx>

DEFINE_TEST("<>")
{
  auto opt_uri = uri::uri::try_parse("");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_FALSE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_FALSE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_TRUE(uri.path_str().empty());
}

DEFINE_TEST("<http:///index.html>")
{
  auto opt_uri = uri::uri::try_parse("http:///index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), true);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), true);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), false);
  TEST_EQUAL((bool)uri.fragment(), false);

  TEST_EQUAL(uri.scheme_str(), "http");
  TEST_EQUAL(uri.host_str(), "");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("<http://host.domain./index.html>")
{
  auto opt_uri = uri::uri::try_parse("http://host.domain./index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "http");
  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("<https://host.domain.:8443/index.html>")
{
  auto opt_uri = uri::uri::try_parse("https://host.domain.:8443/index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("<https://host.domain.:8443/search?q=hamsters>")
{
  auto opt_uri =
    uri::uri::try_parse("https://host.domain.:8443/search?q=hamsters");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
}

DEFINE_TEST("<https://host.domain.:8443/search?q=hamsters#results>")
{
  auto opt_uri =
    uri::uri::try_parse("https://host.domain.:8443/search?q=hamsters#results");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_TRUE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_TRUE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
  TEST_EQUAL(uri.fragment_str(), "results");
}

DEFINE_TEST("<https://admin:qwerty@host.domain.:8443/search?q=hamsters#results>")
{
  auto opt_uri = uri::uri::try_parse(
    "https://admin:qwerty@host.domain.:8443/search?q=hamsters#results");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_TRUE((bool)uri.scheme());
  TEST_TRUE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_TRUE((bool)uri.port());
  TEST_TRUE((bool)uri.query());
  TEST_TRUE((bool)uri.fragment());

  TEST_EQUAL(uri.scheme_str(), "https");
  TEST_EQUAL(uri.userinfo_str(), "admin:qwerty");
  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.port_str(), "8443");
  TEST_EQUAL(uri.path_str(), "/search");
  TEST_EQUAL(uri.query_str(), "q=hamsters");
  TEST_EQUAL(uri.fragment_str(), "results");
}

DEFINE_TEST("<//host.domain./index.html>")
{
  auto opt_uri = uri::try_parse_uri("//host.domain./index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_FALSE((bool)uri.scheme());
  TEST_FALSE((bool)uri.userinfo());
  TEST_TRUE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.host_str(), "host.domain.");
  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("</index.html>")
{
  auto opt_uri = uri::try_parse_uri("/index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_FALSE((bool)uri.userinfo());
  TEST_FALSE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.path_str(), "/index.html");
}

DEFINE_TEST("<index.html>")
{
  auto opt_uri = uri::try_parse_uri("index.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_FALSE((bool)uri.userinfo());
  TEST_FALSE((bool)uri.host());
  TEST_FALSE((bool)uri.port());
  TEST_FALSE((bool)uri.query());
  TEST_FALSE((bool)uri.fragment());

  TEST_EQUAL(uri.path_str(), "index.html");
}

DEFINE_TEST("</files/index:1.html>")
{
  auto opt_uri = uri::try_parse_uri("/files/index:1.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), false);
  TEST_EQUAL((bool)uri.fragment(), false);

  TEST_EQUAL(uri.path_str(), "/files/index:1.html");
}

DEFINE_TEST("<files/index:1.html>")
{
  auto opt_uri = uri::try_parse_uri("files/index:1.html");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), false);
  TEST_EQUAL((bool)uri.fragment(), false);

  TEST_EQUAL(uri.path_str(), "files/index:1.html");
}

DEFINE_TEST("<?q=hamsters>")
{
  auto opt_uri = uri::try_parse_uri("?q=hamsters");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), true);
  TEST_EQUAL((bool)uri.fragment(), false);

  TEST_EQUAL(uri.query_str(), "q=hamsters");
}

DEFINE_TEST("<?q=hamsters#results>")
{
  auto opt_uri = uri::try_parse_uri("?q=hamsters#results");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), true);
  TEST_EQUAL((bool)uri.fragment(), true);

  TEST_EQUAL(uri.query_str(), "q=hamsters");
  TEST_EQUAL(uri.fragment_str(), "results");
}

DEFINE_TEST("<#results>")
{
  auto opt_uri = uri::try_parse_uri("#results");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), false);
  TEST_EQUAL((bool)uri.fragment(), true);

  TEST_EQUAL(uri.fragment_str(), "results");
}

DEFINE_TEST("<#results?gui-sort=asc>")
{
  auto opt_uri = uri::try_parse_uri("#results?gui-sort=asc");

  TEST_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  TEST_EQUAL((bool)uri.scheme(), false);
  TEST_EQUAL((bool)uri.userinfo(), false);
  TEST_EQUAL((bool)uri.host(), false);
  TEST_EQUAL((bool)uri.port(), false);
  TEST_EQUAL((bool)uri.query(), false);
  TEST_EQUAL((bool)uri.fragment(), true);

  TEST_EQUAL(uri.fragment_str(), "results?gui-sort=asc");
}
