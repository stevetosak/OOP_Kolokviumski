#include <iostream>
#include <cstdlib>
#include <cstring>

class Image{
protected:
    char* name;
    char username[50];
    int width = 800;
    int height = 800;
public:
    Image(){
        name = new char[9];
        strcpy(this->name,"untitled");
        strcpy(username,"unknown");
    }
    Image(char* name){
        this->name = new char [strlen(name)+1];
        strcpy(this->username,"unknown");
        strcpy(this->name,name);
    }
    Image(char* name, char*username){
        this->name = new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->username,username);
    }
    Image(char* name, char*username,int w, int h){
        this->name = new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->username,username);
        this->width = w;
        this->height = h;
    }
    Image(const Image& other){
        delete [] name;
        this->name = new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->username,other.username);
        this->width = other.width;
        this->height = other.height;
    }
    bool operator > (Image& img){
        return (this->fileSize() > img.fileSize());
    }
    Image& operator = (const Image& other){
        if(this != &other){
            delete [] name;
            this->name = new char [strlen(other.name)+1];
            strcpy(this->name,other.name);
            strcpy(this->username,other.username);
            this->width = other.width;
            this->height = other.height;
            return *this;
        }
        return *this;
    }
    virtual int fileSize(){
        return width * height * 3;
    }
    virtual ~Image(){
        delete [] name;
    }
    friend std::ostream& operator << (std::ostream& os, Image& img);
};
class TransparentImage : public Image{
private:
    bool hasOpacity;
public:
    TransparentImage() : Image(){
        hasOpacity = true;
    }
    TransparentImage(char* name, char*username,int w, int h,bool hasOpacity) : Image(name,username,w,h){
        this->hasOpacity = hasOpacity;
    }
    TransparentImage(const TransparentImage& other) : Image((Image&)other){
        this->hasOpacity = other.hasOpacity;
    }
    int fileSize(){
        if(hasOpacity){
            return width * height * 4;
        }
        else{
            return (width * height + ((width * height)/8));
        }
    }
};

class Folder{
private:
    char name[255];
    char username[50];
    Image* images[100];
    int numImages;
public:
    Folder(){
        strcpy(username,"unknown");
        numImages = 0;
    }
    Folder(char* name, char* username){
        strcpy(this->name,name);
        strcpy(this->username,username);
    }
    int folderSize(){
        int total = 0;
        for(int i = 0; i < numImages; i++){
            total+=images[i]->fileSize();
        }
        return total;
    }
    Image* getMaxFile(){
        int maxID = -1;
        float max = 0;
        for(int i = 0; i < numImages; i++){
            if(images[i]->fileSize() > max){
                maxID = i;
                max = images[i]->fileSize();
            }
        }
        return images[maxID];
    }
    Folder& operator += (Image& img){
        if(numImages>=100){
            return *this;
        }
        else {
            if(dynamic_cast<TransparentImage*> (&img)){
                TransparentImage* trimg = (TransparentImage*)&img;
                images[numImages] = new TransparentImage(*trimg);
                numImages++;
            }
            else{
                images[numImages] = new Image(img);
                numImages++;
            }

            return *this;
        }
    }
    Image* operator [] (int id) const{
        if(id >= numImages || id < 0){
            return NULL;
        }
        else{
            return images[id];
        }
    }
    friend std::ostream& operator << (std::ostream& os, Folder& fld);
};

std::ostream& operator << (std::ostream& os, Image& img){
    os << img.name << " " << img.username << " " << img.fileSize() << std::endl;
    return os;
}
std::ostream& operator << (std::ostream& os, Folder& fld){
    os << fld.name <<  " " << fld.username << std::endl;
    os << "--" << std::endl;

    for(int i = 0; i < fld.numImages; i++){
        os << *fld.images[i];
    }

    os << "--" << std::endl;
    os << "Folder size: " << fld.folderSize() << std::endl;
    return os;
}

Folder& max_folder_size(Folder* fldrs, int numFolders){
    int maxID = -1;
    float max = 0;
    for(int i = 0; i < numFolders; i++){
        if(fldrs[i].folderSize() > max){
            maxID = i;
            max = fldrs[i].folderSize();
        }
    }
    return fldrs[maxID];
}

using namespace std;


int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
