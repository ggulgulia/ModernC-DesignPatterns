#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>


struct Image{

    virtual void draw() = 0;
};

struct BitMap : public Image{
    BitMap(const std::string& fileName){
        std::cout << "Loading bitmap from " << fileName << "\n";
    }

    void draw() override{
        std::cout << "Drawing BitMap\n";
    }
};

struct LazyBitMap : public Image{

    private:
        std::string m_fileName;
        std::unique_ptr<BitMap> m_bmp;
    public:
        LazyBitMap(const std::string& fileName): m_fileName(fileName){
    
        }

        void draw () override{
            if(!m_bmp){
                m_bmp = std::make_unique<BitMap>(m_fileName);
                m_bmp->draw();
            }
        }

};


int main(){
    BitMap bmp{"pokemon.png"};
    bmp.draw();
    LazyBitMap bmp2{"pokemon.png"};
    bmp2.draw();
    return 0;
}
