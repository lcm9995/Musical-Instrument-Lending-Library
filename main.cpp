//Lily McAmis
//Rec10
//CS2124

#include <iostream>
#include <vector>
using namespace std;

class Instrument{
    friend ostream& operator<<(ostream& os, const Instrument& inst){
        inst.display(os);
        return os;
    }
public:
    virtual void display(ostream& os)const=0;
    virtual void makeSound()const=0;
    virtual void play()const=0;
};



class Brass : public Instrument{
public:
    explicit Brass(unsigned size){
        /*if(size != 12 && size != 9 && size!=4){
            cerr << "Invalid Moutpiece size\n";
            exit(1);
        }else{*/
        mouthpiece_size = size;
    }
    unsigned getMouthpieceSize() const {
        return mouthpiece_size;
    }
    void makeSound()const{
        cout << "To make a sound... blow on a mouthpiece of size "
             << mouthpiece_size<< "\n";
    }
    void display(ostream& os) const {
       // os << this->getType()<< " : " << mouthpiece_size <<"\n";
        //this->display(os);
    }
    //virtual const string& getType() const=0;

private:
    unsigned mouthpiece_size;

};

class String : public Instrument{
public:
    String(unsigned thePitch): pitch(thePitch){}
    unsigned getPitch() const{
        return pitch;
    }
    void makeSound()const{
        cout << "To make a sound... bow a string with pitch "<< pitch << "\n";
    }
   // void display(ostream& os) const{
       // cout<< this->getType()<< " : " << pitch<<"\n";
   // }
        //this->display(os);
    //}
    //virtual const string& getType() const=0;

private:
    const unsigned pitch;
};

class Percussion : public Instrument{
public:
    void makeSound()const{
        cout << "To make a sound... hit me!\n";
    }
    //void display(ostream& os)const {
        //this->display(os);
   // }
};

class Drum : public Percussion{
public:
    Drum(){};
    void display(ostream& os)const{
        os << "Drum: \n";
    }
    void play()const{
        cout << "Boom";
    }

};
class Cymbal : public Percussion{
public:
    Cymbal(){};
    void display(ostream& os)const{
        os<< "Cymbal: \n";
    }
    void play()const{
        cout << "Crash";
    }
};

class Cello: public String{
public:
    Cello(unsigned pitch) : String(pitch){}
    void display(ostream& os)const{
        os<< "Cello: " << this->getPitch() << " \n";
    }
    void play()const{
        cout << "Squawk";
    }
};

class Violin : public String{
public:
    Violin(unsigned pitch): String(pitch){}
    void display(ostream& os)const{
        os<< "Violin: " << this->getPitch() << " \n";
    }
    void play()const{
        cout << "Screech";
    }
};

/*class Big : public Brass{
    Big(): Brass(12){}
private:
    //unsigned mouthpiece_size;
};
class Medium : public Brass{
    Medium(): Brass(9){}
};
class Small : public Brass{
    Small() : Brass(4){}
};*/
class Trumpet : public Brass{
public:
    Trumpet(unsigned size) : Brass(size){}
    void display(ostream& os)const{
        os<< "Trumpet " << this->getMouthpieceSize() << " \n";
    }
    void play()const{
        cout<<"Toot";
    }
};

class Trombone : public Brass{
public:
    Trombone(unsigned size) : Brass(size){}
    void display(ostream& os)const{
        os<< "Trombone: " << this->getMouthpieceSize() << " \n";
    }
    void play()const{
        cout<<"Blat";
    }
};

//class Trumpet: public Brass{
//Trumpet(unsigned size): Brass(size){}

//};


//
// Musician class as provided to the students. Requires an Instrument class.
//

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
       // else cerr << name << " has no instr\n";
        //exit(1);
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play()const {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};



class MILL{
    friend ostream& operator<<(ostream& os, const MILL& mill){
        //if (mill.is_empty())
        os << "The MILL has the following instruments: \n";
        bool empty=true;
        //os << "\n";
        for (size_t i =0; i< mill.inventory.size(); i++){
            if (mill.inventory[i] != nullptr){
                //os << "\n";
                mill.inventory[i]->display(os);
                empty = false;
            }
        }
        if(empty){
            os << "None\n";
        }
        return os;
    }
public:
    MILL(): inventory(0){}
    void receiveInstr(Instrument& instrument ){
        //make sound
        instrument.makeSound();
        bool freespace=false;
        size_t ind = 0;
        while ((ind < inventory.size()) && (freespace == false)){
            if (inventory[ind] == nullptr){
                freespace = true;
                inventory[ind]=&instrument;
            }
            ++ind;
        }
        //for (size_t i = 0; i< inventory.size(); i++){
            //if (inventory[i]==nullptr){
                //freespace = true;
               // inventory[i] = &instrument;
            //}
       // }
        if (freespace==false){
            inventory.push_back(&instrument);
        }
    }
    Instrument* loanOut(){
        for (size_t i = 0; i< inventory.size(); i++){
            if(inventory[i] != nullptr){
                Instrument* const temp = inventory[i];
                inventory[i]=nullptr;
                return temp;
            }
        }
        return nullptr;
    }
    void dailyTestPlay()const{
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i]!=nullptr){
                inventory[i]->makeSound();
            }
        }
    }
private:
    vector<Instrument*> inventory;

};
class Orch{
public:
    Orch(): musicians(0){}
    void addPlayer(Musician& musician){
        Musician* newplayer = &musician;
        musicians.push_back(newplayer);
    }
    void play()const{
        for (size_t i = 0; i < musicians.size(); i++){
            musicians[i]->play();
        }
        cout << "\n";
    }

private:
    vector<Musician*> musicians;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //cout << endl << mill << endl;*/

}


