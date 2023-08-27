#ifndef SCRAPER_H
#define SCRAPER_H

#include <unordered_set>
#include <string>
#include <vector>

bool isValid(const std::string& link);
std::unordered_set<std::string> findWikiLinks(const std::string& page_html);
int nCommonLinks(const std::unordered_set<std::string>& s1,
                 const std::unordered_set<std::string>& s2);
std::vector<std::string> findWikiLadder(const std::string& start_page,
                                        const std::string& end_page);

#endif
