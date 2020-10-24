## Save-State Algorithm
Save-state algorithm allows for system objects to be saved and loaded to/from binary files.  

# Creating Conforming Class 
All classes, whose objects want to be saved, must inherit SaveState; create load, save, and report methods; and create static class id and static New method for dynamic object load.



```
// Constructor for Dynamic Object Load
class::Constructor(unsigned int id) : SaveState(classId, id) {
    // initialize class
}

// called for dynamic object creation
static SaveState * New(unsigned int id){
    return new class(id)
}

static unsigned int classId = this class' unique id
```

Registering
```
SaveSTateClassRegister(class::classId, &class::New)
```
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