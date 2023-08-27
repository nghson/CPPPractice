#include <unordered_set>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "wikiscraper.h"

using std::cout;
using std::string;
using std::unordered_set;
using std::vector;

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
        auto prefix_head = link_prefix.begin();
        auto prefix_end = link_prefix.end();
        auto link_head = std::search(page_html.begin(), page_end, prefix_head, prefix_end);
        while (link_head != page_end) {
                auto link_end = std::find(link_head + 6, page_end, link_suffix);
                string link{link_head + 12, link_end};
                
                if (isValid(link)) {
                        s.insert(link);
                }
                
                link_head = std::search(++link_head, page_end, prefix_head, prefix_end);
        }

        return s;
}

vector<string> findWikiLadder(const string& start_page, const string& end_page)
{
        vector<string> ladder{start_page};

}

int nCommonLinks(const unordered_set<string>& current_set, const unordered_set<string>& target_set)
{
        int n = 0;
        for (auto i = current_set.begin(); i != current_set.end(); ++i) {
                if (target_set.count(*i)) {
                        n++;
                }
        }
        return n;
}