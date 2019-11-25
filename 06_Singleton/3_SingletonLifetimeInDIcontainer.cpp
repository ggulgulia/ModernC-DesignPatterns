#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <memory>
#include <map>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Database{

    public:
        virtual int get_population(const std::string& city_name) =0;
};

class SingletonDataBase : public Database{
    
    private:
        std::map<std::string, int> m_capitals;

        //Note the constructor is private 
        //meaning that the object cannot be 
        //constructed privately
        SingletonDataBase() {
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

    //the method is static and copy constructor is deleted 
    //meaning that the `SingletonDatabase` object created by
    //this method cannot be assigned to a SingletonDatabase object
    static SingletonDataBase& get(){
        static SingletonDataBase db;
        return db;
    }

    static SingletonDataBase* get1(){
        static SingletonDataBase* db = new SingletonDataBase();
        return db;
    }

    int get_population(const std::string& city_name) override{
        return m_capitals[city_name];
    }

};

class DummyDatabase : public Database
{
private:
    /* data */
    std::map<std::string, int> m_capitals1;
public:
    DummyDatabase (){
        m_capitals1["alpha"] = 1;
        m_capitals1["beta"] = 2;
        m_capitals1["gamma"] = 3;
    }
    virtual ~DummyDatabase () = default;
    int get_population(const std::string& city_name) override{
        return m_capitals1[city_name];
    }

};

struct SingletonRecordFinder{

    int total_population(const std::vector<std::string>& names){
        int result{0};
        for(auto& name: names){
            result += SingletonDataBase::get().get_population(name);
        }
        return result;
    }
};

struct ConfigurableRecordFinder{
    Database& m_db;
    ConfigurableRecordFinder(Database& db): m_db(db){
    }

    int total_population(const std::vector<std::string>& names){
        int result{0};
        for(auto& name : names){
            result += m_db.get_population(name);
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

TEST(RecordFinderTest, DependentTotalPopulationTest){
    DummyDatabase db2;
    ConfigurableRecordFinder rf{db2};
    EXPECT_EQ(4, rf.total_population({"alpha", "gamma"}));
}

int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
 = default;
