## Save-State Algorithm
Save-state algorithm allows for system objects to be saved and loaded to/from binary files.  

# Creating Conforming Class 
All classes, whose objects want to be saved, must inherit SaveState; create load, save, get class id, and report virtual methods; and create static class id and static New method for dynamic object load.

Using generatic class, the following is the methods a class must implement:
```
// Constructor for Dynamic Object Load
// Initialization will be taken care of by SaveState Manager using loadFile
Constructor(unsigned int id) : SaveState(id) {}

// called for dynamic object creation
static SaveState * New(unsigned int id){
    return new class(id)
}

// returns class id
unsigned int GetClassId() { return classId; }

// Save object variables
void Save(ofstream& saveFile){
    // Saving using fstream's binary write function { file.write((char*)&variable, sizeof(variable)) }

    // for pointer pointing to SaveState object, you save the object ID instead of the object. This allows you to search SaveStateList on loading
}  

// Load object variables
void Load(ifstream& loadFile){
    // load using fstream's binary read function { file.read((char*)&variable, sizeof(variable)) }
}

// Repoint pointers pointing to SaveState child objects
void Repoint(const std::vector<SaveState*>& SaveStateList){
    // find object by searching SaveStateList for object id (the object the pointer was pointing at)
}

static unsigned int classId = this class' unique id
```

Registering class with SaveState:
```
SaveStateClassRegister(class::classId, &class::New)
```
This allows for dynamic loading (creating dynamic objects). 

# Process Work Flow
```
System Execution:
    Register Classes w/Save-State Manager 
    Create Initial System States
    if load:
        SaveStateLoad(load binary file)
    System Control-loop:
        System Processes
        if save:
            SaveStateSave(save binary file)
```