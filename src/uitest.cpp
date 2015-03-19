// UITest - Simple testing framework for interactive tests
// Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <uitest/uitest.hpp>

namespace uitesting {

std::vector<std::unique_ptr<TestInfo> > g_tests;

TestInfo*
register_test(const std::string& _class, const std::string& _func,
                         const std::function<std::unique_ptr<UITest> ()>& factory,
                         const std::string& args_str, const std::string& doc)
{
  boost::tokenizer<> tok(args_str);
  std::vector<std::string> args(std::begin(tok), std::end(tok));
  g_tests.push_back(
    std::unique_ptr<TestInfo>(
      new TestInfo{_class + "." + _func, _class, _func, args_str, args, doc, factory}));

  std::cout << "reg " << _class << "." << _func << ": " << &g_tests << " " << g_tests.back().get() << " " << g_tests.size() << std::endl;

  return g_tests.back().get();
}

TestInfo*
find_testcase(const std::string& testcase)
{
  for(const auto& testinfo : g_tests)
  {
    std::cout << "* " << testinfo->m_name << std::endl;
    if (testinfo->m_name == testcase)
    {
      return testinfo.get();
    }
  }
  return nullptr;
}

} // namespace uitesting

/* EOF */
