#include <gtest.h>
#include "list.h"

TEST(Iterator, iterator_can_be_dereferenced) {
    List l(3);
    l[0] = 50;
    EXPECT_EQ(*(l.begin()), 50);
}

TEST(Iterator, can_increment_iterator) {
    List l(3);
    l[1] = 50;
    l[2] = 100;
    List::Iterator it = l.begin();
    it++;
    EXPECT_EQ(*it,50);
    ++it;
    EXPECT_EQ(*it, 100);
}

TEST(Iterator, can_increase_iterator_by_value) {
    List l(5);
    l[4] = 100;
    EXPECT_EQ(*(l.begin() + 4), 100);
}

TEST(Iterator, throws_when_add_too_large_value) {
    List l(3);
    
    ASSERT_ANY_THROW(List::Iterator it = l.begin() + 4;);
}

TEST(Iterator, iterator_is_not_equal) {
    List l(3);
    List::Iterator it1 = l.begin();
    List::Iterator it2 = it1;
    ++it2;
    EXPECT_TRUE(it1 != it2); 
}

TEST(Iterator, begin_is_equal_nullptr_in_empty_list) {
    List l;
    EXPECT_EQ(l.begin(), nullptr); 
}

TEST(Iterator, incrementing_past_end) {
    List l(2);
    List::Iterator it = l.begin()+2;
    EXPECT_EQ(it, l.end());     
}