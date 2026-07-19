public class Solution {
public String minWindow(String s, String t) {
    if(s == null || s.length() < t.length() || s.length() == 0){
        return "";
    }
    HashMap<Character,Integer> map = new HashMap<Character,Integer>();
    for(char c : t.toCharArray()){
        if(map.containsKey(c)){
            map.put(c,map.get(c)+1);
        }else{
            map.put(c,1);
        }
    }
    int left = 0;
    int minLeft = 0;
    int minLen = s.length()+1;
    int count = 0;
    for(int right = 0; right < s.length(); right++){
        if(map.containsKey(s.charAt(right))){
            
            System.out.println(map.get(s.charAt(right)));
            map.put(s.charAt(right),map.get(s.charAt(right))-1);
            System.out.println(map.get(s.charAt(right)));
            if(map.get(s.charAt(right)) >= 0){
                count ++;//we found one in t, when count go to the t size, means we found all the letters in t,
              //negative value means for example you need one "a", but you have 2 "a", so the second will make the map count to -1, and 
              //we should not make count ++ because all a was already found.
            }

            while(count == t.length()){
              //keep the state of that we find all letters, under this condition, let's move left pointer : left ++
                
                System.out.println("found" + left + "->"+right);
                if(right-left+1 < minLen){//during the move of left, we could to note the minlen
                    minLeft = left;
                    minLen = right-left+1;
                }
                if(map.containsKey(s.charAt(left))){
                    map.put(s.charAt(left),map.get(s.charAt(left))+1);
                    if(map.get(s.charAt(left)) > 0){//map count become positive means we don't match that char
                        count --;//we increment count to tell the loop : now the situation is that after move left pointer, we don't match all letters in t 
                    }
                }
                left ++ ;//move left
            }
        }
    }
    if(minLen>s.length())  
    {  
        return "";  
    }  
    
    return s.substring(minLeft,minLeft+minLen);
}
}
