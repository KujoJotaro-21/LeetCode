typedef struct stackobj{
    int val;
    struct stackobj* prev;
}stackobj;

typedef struct {
    stackobj* tos;
    int size;
}minstk;

typedef struct {
    stackobj* tos;
    int size;
    minstk* min;
} MinStack;

minstk* minstkcreate() {
    minstk* out=(minstk*)malloc(sizeof(minstk));
    out->tos = NULL;
    out->size = 0;
    return out;
}

MinStack* minStackCreate() {
    MinStack* out=(MinStack*)malloc(sizeof(MinStack));
    out->tos = NULL;
    out->size = 0;
    out->min = minstkcreate();
    return out;
}

int minstktop(minstk* obj) {
    return obj->tos->val;
}

void minstkpush(minstk* obj, int val) {
    stackobj* new = (stackobj*)malloc(sizeof(stackobj));
    if (!new) return;
    new->val = val;
    new->prev = obj->tos;
    obj->tos = new;
    obj->size++;

}

void minStackPush(MinStack* obj, int val) {
    stackobj* new = (stackobj*)malloc(sizeof(stackobj));
    if (!new) return;
    new->val = val;
    new->prev = obj->tos;

    if (!obj->size){
        minstkpush(obj->min,val);
    }    
    obj->tos = new;
    obj->size++;
    if (minstktop(obj->min)>=val) minstkpush(obj->min,val);

}

void minstkpop(minstk* obj) {
    if (!obj->size) return;
    if(obj){
        stackobj* temp = obj->tos;
        obj->tos = temp->prev;
        obj->size--;
        free(temp);
    }
}

void minStackPop(MinStack* obj) {
    if (!obj->size) return;
    if (obj->min->tos->val==obj->tos->val) minstkpop(obj->min); 
    if(obj){
        stackobj* temp = obj->tos;
        obj->tos = temp->prev;
        obj->size--;
        free(temp);
    }
}

int minStackTop(MinStack* obj) {
    return obj->tos->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->min->tos->val;
}

void minstkFree(minstk* obj) {
    while (obj->size) {
        minstkpop(obj);
    }
    free(obj);
}

void minStackFree(MinStack* obj) {
    while (obj->size) {
        minStackPop(obj);
    }
    minstkFree(obj->min);
    free(obj);
}


/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
