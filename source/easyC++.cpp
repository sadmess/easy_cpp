
#include<iostream>
#include<memory>
#include<vector>
#include<deque>
#include<queue>
#include<stdio.h>
/*template <typename T>
void FreeAll(T& t) {
    T tmp;
    t.swap(tmp);
}*/
class Note {
public:
    virtual void getEncourageImpl() = 0;
};

class NoteImpl : Note {
public:
    NoteImpl() {
        gitf1.reserve(0x5);
        note_.reserve(0x5);
    };
    void getEncourageImpl() { std::cout << "You can shell me!" << std::endl; };
    void add() {

        char tmp = 0;
        if (cleared_ == false) {
            std::cout << "Do you want to clear it?(y/N)" << std::endl;
            std::cin >> tmp;
            if (tmp == 'y' && cleared_ == false) {
                std::cout << "you can only clear once!!" << std::endl;
                note_.clear();
                cleared_ = true;
            }
        }
        std::cout << "content(q to quit):" << std::endl;
        while (std::cin >> tmp) {
            if (tmp == 'q')
                break;
            if (note_.size() > 0x1000) {
                std::cout << "nonono!" << std::endl;
                exit(0);
            }
            note_.push_back(tmp);
        }
    }
    void save() {
        note_.shrink_to_fit();
    }
private:
    bool cleared_ = false;
    std::vector<char> note_;
    char pad1[0x178];
    std::vector<char> gitf1;
    void* gift2 = (void*)malloc;
    char pad2[0x180];

};

class NoteDBImpl {
    bool isdelete;
    NoteImpl* note_ptr_bk_;
public:
    NoteDBImpl(NoteImpl* inner_db) : isdelete(false), note_ptr_bk_(inner_db) {
    }
    void getEncourage() {
        if (*(int*)note_ptr_bk_)
            note_ptr_bk_->getEncourageImpl();
    }
    void setdel() {
        isdelete = true;
    }
    void gift() {
        if (isdelete) {
            printf("%s\n", note_ptr_bk_);
        }
    }
};

class NoteStorageImpl {

    std::unique_ptr<NoteImpl> note_ptr_[2];
    std::unique_ptr<NoteDBImpl> note_db_ptr_;
public:
    void init() {
        note_ptr_[0] = std::make_unique<NoteImpl>();
        note_ptr_[1] = std::make_unique<NoteImpl>();
    }
    void backup() {
        if (!note_db_ptr_)
            note_db_ptr_ = std::make_unique<NoteDBImpl>(note_ptr_[0].get());
    }
    void editHouse() {
        if (!note_ptr_[0]) {
            note_ptr_[1].get()->add();
            return;
        }
        note_ptr_[0].get()->add();
    }
    void saveHouse() {
        if (note_ptr_[0])
            note_ptr_[0].get()->save();
        else if (note_ptr_[1])
            note_ptr_[1].get()->save();
        else
            std::cout << "You have no house to save!!!" << std::endl;
    }
    void encourage() {
        if (note_db_ptr_)
            note_db_ptr_.get()->getEncourage();
        else
            std::cout << "You can not get encourage now!" << std::endl;
    }
    void delHouse() {
        if (note_db_ptr_) {
            note_db_ptr_.get()->setdel();
            note_ptr_[0].reset();
        }
        else
            std::cout << "You can not delete now!" << std::endl;
    }
    void show() {
        if (note_db_ptr_)
            note_db_ptr_.get()->gift();
        else
            std::cout << "NO!" << std::endl;
    }
};


int main() {
    NoteStorageImpl* mynote = new NoteStorageImpl();
    mynote->init();
    int choice = 0;
    while (1) {
        std::cout << "1.editHouse" << std::endl;
        std::cout << "2.reconditionHouse" << std::endl;
        std::cout << "3.backupHouse" << std::endl;
        std::cout << "4.encourage" << std::endl;
        std::cout << "5.delHouse" << std::endl;
        std::cout << "6.show" << std::endl;
        std::cout << ">> ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            mynote->editHouse();
            break;
        case 2:
            mynote->saveHouse();
            break;
        case 3:
            mynote->backup();
            break;
        case 4:
            mynote->encourage();
            break;
        case 5:
            mynote->delHouse();
            break;
        case 6:
            mynote->show();
        default:
            break;
        }
    }
}
