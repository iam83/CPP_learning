#include <iostream>

struct Advertising{

	int ad_amount;
	double visitors_percent;
	double median_revenue;

};

void print_sum(Advertising adverts){
	std::cout << "Adverts amount: " << adverts.ad_amount << std::endl;
	std::cout << "Viewed by: " << adverts.visitors_percent << "%" << std::endl;
	std::cout << "Median revenue: " << adverts.median_revenue << std::endl;

	std::cout << "You've earned: " << (adverts.ad_amount * adverts.visitors_percent / 100 * adverts.median_revenue)
			  << std::endl;
}

int main(){

	Advertising adverts {20,20,20};
	print_sum(adverts);
	return 0;

}