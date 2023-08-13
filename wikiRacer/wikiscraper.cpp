#include <unordered_set>
#include <string>
#include <algorithm>
#include <iostream>
#include "wikiscraper.h"

using std::string;
using std::unordered_set;
using std::cout;

/*
A link must be of the form
<a href="/wiki/PAGE_NAME">text</a>
and PAGE_NAME doesn't contain # or :
*/

bool isValid(const string& link)
{
        return std::all_of(link.begin(), link.end(), [](char c) {
                return c != '#' && c != ':';
        });
}

unordered_set<string> findWikiLinks(const string& page_html)
{
        unordered_set<string> s;

        const string link_prefix = "href=\"/wiki/";
        const char link_suffix = '\"';
        
        auto page_end = page_html.end();
        auto l1 = link_prefix.begin();
        auto l2 = link_prefix.end();
        auto link_head = std::search(page_html.begin(), page_end, l1, l2);
        while (link_head != page_end) {
                auto link_end = std::find(link_head + 6, page_end, link_suffix);
                string link{link_head + 12, link_end};
                
                if (isValid(link)) {
                        s.insert(link);
                }
                
                link_head = std::search(++link_head, page_end, l1, l2);
        }

        return s;
}
