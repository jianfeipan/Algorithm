class Solution {
    /*
    Given two version numbers, version1 and version2, compare them.

Version numbers consist of one or more revisions joined by a dot '.'. Each revision consists of digits and may contain leading zeros. Every revision contains at least one character. Revisions are 0-indexed from left to right, with the leftmost revision being revision 0, the next revision being revision 1, and so on. For example 2.5.33 and 0.1 are valid version numbers.

To compare version numbers, compare their revisions in left-to-right order. Revisions are compared using their integer value ignoring any leading zeros. This means that revisions 1 and 001 are considered equal. If a version number does not specify a revision at an index, then treat the revision as 0. For example, version 1.0 is less than version 1.1 because their revision 0s are the same, but their revision 1s are 0 and 1 respectively, and 0 < 1.

Return the following:

If version1 < version2, return -1.
If version1 > version2, return 1.
Otherwise, return 0.


Fact:
    1 0 in front ignored
    2 left big digit, right null is 0


Idea:
    read until next '.' and compare then next...
    base case: empty


*/
public:
    int compareVersion(string version1, string version2) {
        std::stringstream ss1(version1);
        std::string versionNum1;        
        std::stringstream ss2(version2);
        std::string versionNum2;
        
        bool version1HasValue = !!std::getline(ss1, versionNum1, '.');
        bool version2HasValue = !!std::getline(ss2, versionNum2, '.');

        while( version1HasValue||version2HasValue)
        {
            if(version1HasValue && version2HasValue)
            {
                int v1 = stoi(versionNum1);
                int v2 = stoi(versionNum2);



                if(v1 < v2) return -1;
                if(v1 > v2) return 1;

                version1HasValue = !!std::getline(ss1, versionNum1, '.');
                version2HasValue = !!std::getline(ss2, versionNum2, '.');
            }
            else if(version1HasValue)
            {
                int v1 = stoi(versionNum1);
                if(v1!=0)  return 1;
                version1HasValue = !!std::getline(ss1, versionNum1, '.');
            }
            else if(version2HasValue)
            {
                int v2 = stoi(versionNum2);
                if(v2!=0)  return -1;
                version2HasValue = !!std::getline(ss2, versionNum2, '.');
            }

        };

        return 0;
        
    }
};
