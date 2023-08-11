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

unordered_set<string> findWikiLinks(const string& page_html)
{
        unordered_set<string> s;

        string link_prefix = "href=\"/wiki/";
        
        auto page_end = page_html.end();
        auto l1 = link_prefix.begin();
        auto l2 = link_prefix.end();
        auto link_head = std::search(page_html.begin(), page_end, l1, l2);
        while (link_head != page_end) {
                auto link_end = std::find(link_head + 6, page_end, '\"');
                string link{link_head, ++link_end};
                cout << "The link is " << link << '\n';
                s.insert(link);
                
                link_head = std::search(++link_head, page_end, l1, l2);
        }

        return s;
}
