

#ifndef BOOST_REGEX_REGRESS_TEST_NOT_REGEX_HPP
#define BOOST_REGEX_REGRESS_TEST_NOT_REGEX_HPP
#include "info.hpp"
//
// this file implements a test for a regular expression that should not compile:
//
struct test_invalid_regex_tag{};

template<class charT, class traits>
void test(boost::basic_regex<charT, traits>& r, const test_invalid_regex_tag&)
{
   const std::basic_string<charT>& expression = test_info<charT>::expression();
   boost::regex_constants::syntax_option_type syntax_options = test_info<charT>::syntax_options();
   bool have_catch = false;
   try{
      r.assign(expression, syntax_options);
   }
   catch(const boost::bad_expression&)
   {
      have_catch = true;
   }
   catch(const std::runtime_error& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::runtime_error instead: " << r.what(), charT);
   }
   catch(const std::exception& r)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but a std::exception instead: " << r.what(), charT);
   }
   catch(...)
   {
      have_catch = true;
      BOOST_REGEX_TEST_ERROR("Expected a bad_expression exception, but got an exception of unknown type instead", charT);
   }
   if(!have_catch)
   {
      // oops expected exception was not thrown:
      BOOST_REGEX_TEST_ERROR("Expected an exception, but didn't find one.", charT);
   }

}



#endif