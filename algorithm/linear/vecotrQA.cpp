
/*
Right way to remove elements using remove if
*/
myList.erase(
    std::remove_if(myList.begin(), myList.end(),
        [](const myobj & o) { return o.m_bMarkedDelete; }),
    myList.end());
