#include "../gtests/gtest.h"
#include "../Polinom/polinom.h"

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom pol;);
}

TEST(Polinom, can_add_monom)
{
	Polinom pol;
	pol.insert(201, 8);
	EXPECT_EQ(NULL, !(pol.find(201)));
}

TEST(Polinom, can_not_add_monom_with_zero_fact)
{
	Polinom pol;
	pol.insert(111, 0);
	EXPECT_EQ(NULL, pol.find(111));
}

TEST(Polinom, equal_polinoms)
{
	Polinom pol1;
	pol1.insert(325, 7);
	Polinom pol2;
	Polinom pol3;
	pol2 = pol1;
	pol3 = pol1;
	EXPECT_EQ(true, pol2 == pol3);
}

TEST(Polinom, equal_degree)
{
	Polinom pol1;
	pol1.insert(111, 3);
	pol1.insert(111, 4);
	EXPECT_EQ(true, pol1.boolfind(111));
}

TEST(Polinom, equal_degree_with_positive_and_negative_fact)
{
	Polinom pol1;
	pol1.insert(111, -3);
	pol1.insert(111, 3);
	EXPECT_EQ(NULL, pol1.find(111));
}

TEST(Polinom, can_add_monom_with_incorrect_degree)
{
	Polinom pol1;
	ASSERT_ANY_THROW(pol1.insert(1111,2));
}

TEST(Polinom, can_add_monom_with_negative_degree)
{
	Polinom pol1;
	ASSERT_ANY_THROW(pol1.insert(-1, 2));
}

TEST(Polinom, can_delete_monom)
{
	Polinom pol1;
	pol1.insert(111, 2);
	pol1.insert(112, 3);
	pol1.del(111, 2);
	EXPECT_EQ(NULL, pol1.find(111));
}

TEST(Polinom, can_mul_fact)
{
	Polinom pol1;
	pol1.insert(0, 5);
	Polinom pol2;
	pol2 = pol1 * (-1);
	EXPECT_EQ(true, pol2.boolfind(0));
}

TEST(Polinom, sum_1)
{
	Polinom pol1; 
	pol1.insert(111, 2);
	pol1.insert(222, 3);

	Polinom pol2;
	pol2.insert(101, 3);
	pol2.insert(202, 2);

	Polinom pol3;
	pol3 = pol1 + pol2;

	EXPECT_EQ(true, pol3.boolfind(111));
	EXPECT_EQ(true, pol3.boolfind(101));
	EXPECT_EQ(true, pol3.boolfind(222));
	EXPECT_EQ(true, pol3.boolfind(202));
	EXPECT_EQ(2.0, pol3.find(111)->fact);
	EXPECT_EQ(3.0, pol3.find(101)->fact);
	EXPECT_EQ(3.0, pol3.find(222)->fact);
	EXPECT_EQ(2.0, pol3.find(202)->fact);
}

TEST(Polinom, sum_2)
{
	Polinom pol1;
	pol1.insert(111, 2);
	pol1.insert(222, 3);

	Polinom pol2;
	pol2.insert(111, 3);
	pol2.insert(202, 2);

	pol1 = pol1 + pol2;

	EXPECT_EQ(true, pol1.boolfind(111));
	EXPECT_EQ(true, pol1.boolfind(222));
	EXPECT_EQ(true, pol1.boolfind(202));
	EXPECT_EQ(5, pol1.find(111)->fact);
	EXPECT_EQ(3, pol1.find(222)->fact);
	EXPECT_EQ(2, pol1.find(202)->fact);
}

TEST(Polinom, sum_3)
{
	Polinom pol1;
	pol1.insert(222, 3);

	Polinom pol2;
	pol2.insert(111, 3);
	pol2.insert(202, 2);

	pol1 = pol1 + pol2;

	EXPECT_EQ(true, pol1.boolfind(111));
	EXPECT_EQ(true, pol1.boolfind(222));
	EXPECT_EQ(true, pol1.boolfind(202));
	EXPECT_EQ(3, pol1.find(111)->fact);
	EXPECT_EQ(3, pol1.find(222)->fact);
	EXPECT_EQ(2, pol1.find(202)->fact);
}

TEST(Polinom, sub_1)
{
	Polinom pol1;
	pol1.insert(222, 3);

	Polinom pol2;
	pol2.insert(111, 3);
	pol2.insert(202, 2);

	pol1 = pol2 - pol1;

	EXPECT_EQ(true, pol1.boolfind(111));
	EXPECT_EQ(true, pol1.boolfind(222));
	EXPECT_EQ(true, pol1.boolfind(202));
	EXPECT_EQ(3, pol1.find(111)->fact);
	EXPECT_EQ(-3, pol1.find(222)->fact);
	EXPECT_EQ(2, pol1.find(202)->fact);
}

TEST(Polinom, mul_1)
{
	Polinom pol1;
	pol1.insert(222, 3);

	Polinom pol2;
	pol2.insert(111, 3);
	pol2.insert(202, 2);

	pol1 = pol1 * pol2;

	EXPECT_EQ(true, pol1.boolfind(333));
	EXPECT_EQ(true, pol1.boolfind(424));
	EXPECT_EQ(9, pol1.find(333)->fact);
	EXPECT_EQ(6, pol1.find(424)->fact);
}
