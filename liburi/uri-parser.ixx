namespace uri {

inline optional< uri >
try_parse_uri(std::string const& str)
{
  return try_parse_uri(str.begin(), str.end());
}

} // namespace uri
