#include <iostream>
#include <sstream>
#include <tuple>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <memory>
#include <map>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class SingletonDataBase{
    
    private:
        std::map<std::string, int> m_capitals;
    SingletonDataBase() {
        std::cout << "Initializing database\n";
        std::ifstream ifs("../capitals.txt");
        std::string s1, s2;
        while(getline(ifs, s1)){
            getline(ifs, s2);
            int population = boost::lexical_cast<int>(s2);
            m_capitals[s1] = population;
        }

        ifs.close();
    }

    public:
    SingletonDataBase(const SingletonDataBase&) = delete;
    SingletonDataBase& operator=(const SingletonDataBase&) = delete;

    static SingletonDataBase& get(){
        static SingletonDataBase db;
        return db;
    }

    static SingletonDataBase* get1(){
        static SingletonDataBase* db = new SingletonDataBase();
        return db;
    }

    int get_population(const std::string& city_name){
        return m_capitals[city_name];
    }

};

struct SingletonRecordFinder{

    int total_population(const std::vector<std::string>& names){
        int result{0};
        for(auto& name: names){
            std::cout << name << "\n";
            result += SingletonDataBase::get().get_population(name);
        }
        return result;
    }
};

TEST(SingletonGetTest, SingeltonSingleCityPopulationTest){
    const std::string city{"Berlin"};
    int berlinPopulation = SingletonDataBase::get().get_population(city);
    EXPECT_EQ(20000, berlinPopulation);
}

TEST(RecordFinderTest, SingletonTotalPopulationTest){
    SingletonRecordFinder rf;
    std::vector<std::string> names{"New Delhi", "Kolkata"};
    int tp = rf.total_population(names);
    EXPECT_EQ(100000+300000, tp);
}

int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
