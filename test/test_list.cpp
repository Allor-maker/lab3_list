#include <gtest.h>
#include "list.h"

TEST(List, can_create_empty_list)
{
	List l;
	EXPECT_EQ(l.size(), 0);
}

TEST(List, can_create_not_empty_list)
{
	List l(5);
	EXPECT_EQ(l.size(), 5);
}

TEST(List, can_copy_list)
{
	List l;
	l.insert_front(1);
	l.insert_front(2);
	l.insert_front(3);

	List l2(l);
	EXPECT_EQ(l2.find(3),l2.begin());
	EXPECT_EQ(l2.find(2), l2.begin() + 1);
	EXPECT_EQ(l2.find(1), l2.begin() + 2);
}
TEST(List, can_return_size)
{
	List l(6);
	EXPECT_EQ(l.size(), 6);
}
TEST(List, move_constructor_work_correctly)
{
	List l1;
	l1.insert_front(1);
	l1.insert_front(2);
	l1.insert_front(3);

	List l2(l1);
	List l3 = std::move(l1);

	EXPECT_EQ(*(l2.begin()), *(l3.begin()));
	EXPECT_EQ(*(l2.begin() + 1), *(l3.begin() + 1));
	EXPECT_EQ(*(l2.begin() + 2), *(l3.begin() + 2));
	EXPECT_EQ(l1.size(), 0);
}
TEST(List, can_get_access_to_elem)
{
	List l(3);
	l[0] = 1;
	l[1] = 10;

	EXPECT_EQ(l[0], 1);
	EXPECT_EQ(l[1], 10);
}

TEST(List, can_insert_after)
{
	List l(2);
	l[0] = 1;
	l[1] = 2;
	l.insert_after(10,l[l.begin() + 1]);
	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l[2], 10);
}

TEST(List, can_insert_front)
{
	List l(2);
	l[0] = 1;
	l[1] = 2;
	l.insert_front(3);

	EXPECT_EQ(l.size(), 3);
	EXPECT_EQ(l[0], 3);
}

TEST(List, can_erase_after)
{
	List l(2);

	l[0] = 1;
	l[1] = 10;

	l.erase_after(l[l.begin()]);
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l[0], 1);
}

TEST(List, can_erase_front)
{
	List l(2);

	l[0] = 1;
	l[1] = 10;

	l.erase_front();
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l[0], 10);
}
TEST(List, can_find_elem)
{
	List l(3);
	l[2] = 200;

	EXPECT_EQ(l.find(200), l.begin() + 2);
}

TEST(List, throws_when_try_to_get_access_to_neg_index)
{
	List l(3);

	ASSERT_ANY_THROW(l[-1]);
}

TEST(List, throws_when_try_to_get_access_to_too_large_index)
{
	List l(3);

	ASSERT_ANY_THROW(l[4]);
}

TEST(List, throws_when_try_to_get_access_with_too_large_iterator)
{
	List l(3);

	ASSERT_ANY_THROW(l[l.begin() + 5]);
}

TEST(List, throws_when_create_list_with_neg_length)
{
	ASSERT_ANY_THROW(List l(-1));
}