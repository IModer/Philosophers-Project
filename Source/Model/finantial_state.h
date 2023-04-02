#ifndef FINANATIAL_STATE_STRUCT_DEFINED
#define FINANATIAL_STATE_STRUCT_DEFINED
//mehetne a globalba
struct finantial_state
{
    //lehet egy class update methoddal ahol a rezidensek száma szerint pénzt szed be és adót fizet ki?
    //will see
    int total_founds;
    int loan;
    //lehet float is és akkor százalék
    int residential_tax_rate;
    int industrial_tax_rate;
    int entertainment_tax_rate;
    //this change is purely experimental
};


#endif