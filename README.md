## Save-State Algorithm
This algorithm allows for inherited objects to be saved and loaded from binary files. 


# Work flow
```
System Execution:
    Register Classes w/Save-State Manager 
    Create Initial System States
    if load:
        SaveStateLoad(load binary file)
    System Control-loop:
        System Processes
        if Save:
            SaveStateSave(save binary file)
```