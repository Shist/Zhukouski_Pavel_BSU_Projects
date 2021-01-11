#include "Beer.h" // пиво
#include "Wine.h" // вино
#include "Cognac.h" // коньяк
#include "Milk.h" // молоко
#include "Mineral_Water.h" // минералка
#include "Lemonade.h" // лимонад

int main()
{
	try
	{
		Beer beer_1("Baltic 8", 1000, 5.0, Raw_Mat::Wheat);
		Beer beer_2("Baltic 8", 1500, 5.0, Raw_Mat::Wheat);
		Beer beer_3("Zhigulevskoe", 1000, 2.8, Raw_Mat::Barley);
		Beer beer_4("Zhigulevskoe", 1500, 2.8, Raw_Mat::Barley);
		Beer beer_5("Williams Ginger", 1000, 3.8, Raw_Mat::Ginger);
		Beer beer_6("Williams Ginger", 1500, 3.8, Raw_Mat::Ginger);
		Wine wine_1("Pinot Grigio", 750, 12.5, Color::White);
		Wine wine_2("Pinot Grigio", 1000, 12.5, Color::White);
		Wine wine_3("Red Doctor", 750, 16.0, Color::Red);
		Wine wine_4("Red Doctor", 1000, 16.0, Color::Red);
		Cognac cognac_1("Martell", 1000, 40.0, Excerpt::deLuxe);
		Cognac cognac_2("Martell", 1500, 40.0, Excerpt::Superior);
		Cognac cognac_3("Martell", 2000, 40.0, Excerpt::Vieux);
		Milk milk_1("Valio", 500, 1.9, 14);
		Milk milk_2("Valio", 1000, 1.9, 14);
		Milk milk_3("Prostokvashino", 500, 2.5, 12);
		Milk milk_4("Prostokvashino", 1000, 2.5, 12);
		Milk milk_5("Koshechka", 500, 3.2, 7);
		Milk milk_6("Koshechka", 1000, 3.2, 7);
		Mineral_Water min_w_1("Borjomi", 500, 365, Carbonated::Sparkled);
		Mineral_Water min_w_2("Borjomi", 750, 365, Carbonated::Still);
		Mineral_Water min_w_3("Borjomi", 1000, 365, Carbonated::Sparkled);
		Mineral_Water min_w_4("Borjomi", 1500, 365, Carbonated::Still);
		Lemonade lemonade_1("Snowball", 500, 6, Taste::Lemon);
		Lemonade lemonade_2("Snowball", 1000, 6, Taste::Plum);
		Lemonade lemonade_3("Snowball", 1500, 6, Taste::Coke);
		milk_1.set_exp_date(9); // будем считать, что на складе один из видов молока немного подпортился...
		milk_2.set_exp_date(9); // Это проверочка на сеттер...
		int key = 0;
		cout << "You are in a restaurant. Choose a drink from the list:" << endl;
		cout << "1.Beer" << endl;
		cout << "2.Wine" << endl;
		cout << "3.Cognac" << endl;
		cout << "4.Milk" << endl;
		cout << "5.Mineral water" << endl;
		cout << "6.Lemonade" << endl;
		cin >> key;
		if (key == 1)
		{
			cout << "So, you've chosen beer. Now, choose one from the list:" << endl;
			cout << "1.Baltic 8, 1000 ml, 5% of alcohol, made from wheat" << endl;
			cout << "2.Baltic 8, 1500 ml, 5% of alcohol, made from wheat" << endl;
			cout << "3.Zhigulevskoe, 1000 ml, 2.8% of alcohol, made from barley" << endl;
			cout << "4.Zhigulevskoe, 1500 ml, 2.8% of alcohol, made from barley" << endl;
			cout << "5.Williams Ginger, 1000 ml, 3.8% of alcohol, made from ginger" << endl;
			cout << "6.Williams Ginger, 1500 ml, 3.8% of alcohol, made from ginger" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << beer_1.get_name() << endl;
				cout << "Volume (ml): " << beer_1.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_1.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_1.output_mater(cout);
			}
			else if (key == 2)
			{
				cout << beer_2.get_name() << endl;
				cout << "Volume (ml): " << beer_2.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_2.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_2.output_mater(cout);
			}
			else if (key == 3)
			{
				cout << beer_3.get_name() << endl;
				cout << "Volume (ml): " << beer_3.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_3.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_3.output_mater(cout);
			}
			else if (key == 4)
			{
				cout << beer_4.get_name() << endl;
				cout << "Volume (ml): " << beer_4.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_4.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_4.output_mater(cout);
			}
			else if (key == 5)
			{
				cout << beer_5.get_name() << endl;
				cout << "Volume (ml): " << beer_5.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_5.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_5.output_mater(cout);
			}
			else if (key == 6)
			{
				cout << beer_6.get_name() << endl;
				cout << "Volume (ml): " << beer_6.get_volume() << endl;
				cout << "Percent of alcohol (%): " << beer_6.get_alc_perc() << endl;
				cout << "Basic material: ";
				beer_6.output_mater(cout);
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else if (key == 2)
		{
			cout << "So, you've chosen wine. Now, choose one from the list:" << endl;
			cout << "1.Pinot Grigio, 750 ml, 12.5% of alcohol, white" << endl;
			cout << "2.Pinot Grigio, 1000 ml, 12.5% of alcohol, white" << endl;
			cout << "3.Red Doctor, 750 ml, 16% of alcohol, red" << endl;
			cout << "4.Red Doctor, 1000 ml, 16% of alcohol, red" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << wine_1.get_name() << endl;
				cout << "Volume (ml): " << wine_1.get_volume() << endl;
				cout << "Percent of alcohol (%): " << wine_1.get_alc_perc() << endl;
				cout << "Colour: ";
				wine_1.output_colour(cout);
			}
			else if (key == 2)
			{
				cout << wine_2.get_name() << endl;
				cout << "Volume (ml): " << wine_2.get_volume() << endl;
				cout << "Percent of alcohol (%): " << wine_2.get_alc_perc() << endl;
				cout << "Basic material: ";
				wine_2.output_colour(cout);
			}
			else if (key == 3)
			{
				cout << wine_3.get_name() << endl;
				cout << "Volume (ml): " << wine_3.get_volume() << endl;
				cout << "Percent of alcohol (%): " << wine_3.get_alc_perc() << endl;
				cout << "Basic material: ";
				wine_3.output_colour(cout);
			}
			else if (key == 4)
			{
				cout << wine_4.get_name() << endl;
				cout << "Volume (ml): " << wine_4.get_volume() << endl;
				cout << "Percent of alcohol (%): " << wine_4.get_alc_perc() << endl;
				cout << "Basic material: ";
				wine_4.output_colour(cout);
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else if (key == 3)
		{
			cout << "So, you've chosen cognac. Now, choose one from the list:" << endl;
			cout << "1.Martell, 1000 ml, 40% of alcohol" << endl;
			cout << "2.Martell, 1500 ml, 40% of alcohol" << endl;
			cout << "3.Martell, 2000 ml, 40% of alcohol" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << cognac_1.get_name() << endl;
				cout << "Volume (ml): " << cognac_1.get_volume() << endl;
				cout << "Percent of alcohol (%): " << cognac_1.get_alc_perc() << endl;
			}
			else if (key == 2)
			{
				cout << cognac_2.get_name() << endl;
				cout << "Volume (ml): " << cognac_2.get_volume() << endl;
				cout << "Percent of alcohol (%): " << cognac_2.get_alc_perc() << endl;
			}
			else if (key == 3)
			{
				cout << cognac_3.get_name() << endl;
				cout << "Volume (ml): " << cognac_3.get_volume() << endl;
				cout << "Percent of alcohol (%): " << cognac_3.get_alc_perc() << endl;
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else if (key == 4)
		{
			cout << "So, you've chosen milk. Now, choose one from the list:" << endl;
			cout << "1.Valio, 500 ml, 1.9% of fat content, expiration date: " << milk_1.get_exp_date() << " days" << endl;
			cout << "2.Valio, 100 ml, 1.9% of fat content, expiration date: " << milk_2.get_exp_date() << " days" << endl;
			cout << "3.Prostokvashino, 500 ml, 2.5% of fat content, expiration date: " << milk_3.get_exp_date() << " days" << endl;
			cout << "4.Prostokvashino, 1000 ml, 2.5% of fat content, expiration date: " << milk_4.get_exp_date() << " days" << endl;
			cout << "5.Koshechka, 500 ml, 3.2% of fat content, expiration date: " << milk_5.get_exp_date() << " days" << endl;
			cout << "6.Koshechka, 1000 ml, 3.2% of fat content, expiration date: " << milk_6.get_exp_date() << " days" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << milk_1.get_name() << endl;
				cout << "Volume (ml): " << milk_1.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_1.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_1.get_exp_date() << endl;
			}
			else if (key == 2)
			{
				cout << milk_2.get_name() << endl;
				cout << "Volume (ml): " << milk_2.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_2.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_2.get_exp_date() << endl;
			}
			else if (key == 3)
			{
				cout << milk_3.get_name() << endl;
				cout << "Volume (ml): " << milk_3.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_3.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_3.get_exp_date() << endl;
			}
			else if (key == 4)
			{
				cout << milk_4.get_name() << endl;
				cout << "Volume (ml): " << milk_4.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_4.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_4.get_exp_date() << endl;
			}
			else if (key == 5)
			{
				cout << milk_5.get_name() << endl;
				cout << "Volume (ml): " << milk_5.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_5.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_5.get_exp_date() << endl;
			}
			else if (key == 6)
			{
				cout << milk_6.get_name() << endl;
				cout << "Volume (ml): " << milk_6.get_volume() << endl;
				cout << "Percent of fat content (%): " << milk_6.get_fat_perc() << endl;
				cout << "Expiration date (days): " << milk_6.get_exp_date() << endl;
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else if (key == 5)
		{
			cout << "So, you've chosen mineral water. Now, choose one from the list:" << endl;
			cout << "1.Borjomi, 500 ml, expiration date: " << min_w_1.get_exp_date() << " days" << endl;
			cout << "2.Borjomi, 750 ml, expiration date: " << min_w_2.get_exp_date() << " days" << endl;
			cout << "3.Borjomi, 1000 ml, expiration date: " << min_w_3.get_exp_date() << " days" << endl;
			cout << "4.Borjomi, 1500 ml, expiration date: " << min_w_4.get_exp_date() << " days" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << min_w_1.get_name() << endl;
				cout << "Volume (ml): " << min_w_1.get_volume() << endl;
				cout << "Expiration date (days): " << min_w_1.get_exp_date() << endl;
			}
			else if (key == 2)
			{
				cout << min_w_2.get_name() << endl;
				cout << "Volume (ml): " << min_w_2.get_volume() << endl;
				cout << "Expiration date (days): " << min_w_2.get_exp_date() << endl;
			}
			else if (key == 3)
			{
				cout << min_w_3.get_name() << endl;
				cout << "Volume (ml): " << min_w_3.get_volume() << endl;
				cout << "Expiration date (days): " << min_w_3.get_exp_date() << endl;
			}
			else if (key == 4)
			{
				cout << min_w_4.get_name() << endl;
				cout << "Volume (ml): " << min_w_4.get_volume() << endl;
				cout << "Expiration date (days): " << min_w_4.get_exp_date() << endl;
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else if (key == 6)
		{
			cout << "So, you've chosen lemonade. Now, choose one from the list:" << endl;
			cout << "1.Snowball, 500 ml, expiration date: " << lemonade_1.get_exp_date() << " days" << endl;
			cout << "2.Snowball, 1000 ml, expiration date: " << lemonade_2.get_exp_date() << " days" << endl;
			cout << "3.Snowball, 1500 ml, expiration date: " << lemonade_3.get_exp_date() << " days" << endl;
			cin >> key;
			cout << "So, your order is:" << endl;
			if (key == 1)
			{
				cout << lemonade_1.get_name() << endl;
				cout << "Volume (ml): " << lemonade_1.get_volume() << endl;
				cout << "Expiration date (days): " << lemonade_1.get_exp_date() << endl;
			}
			else if (key == 2)
			{
				cout << lemonade_2.get_name() << endl;
				cout << "Volume (ml): " << lemonade_2.get_volume() << endl;
				cout << "Expiration date (days): " << lemonade_2.get_exp_date() << endl;
			}
			else if (key == 3)
			{
				cout << lemonade_3.get_name() << endl;
				cout << "Volume (ml): " << lemonade_3.get_volume() << endl;
				cout << "Expiration date (days): " << lemonade_3.get_exp_date() << endl;
			}
			else
			{
				cout << "The entered value does not match any of the menu components!" << endl;
			}
		}
		else
		{
			cout << "The entered value does not match any of the menu components!" << endl;
		}
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}