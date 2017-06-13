/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
       assertTrue(urlVal.isValid("http://google.com?test=query"));
       assertFalse(urlVal.isValid("http://256.256.256.256"));
       assertTrue(urlVal.isValid("http://google.com:12345"));
       assertTrue(urlVal.isValid("www.amazon.com"));
       assertTrue(urlVal.isValid("http://www.amazon.com:100"));
       assertTrue(urlVal.isValid("http://amazon.com:1000"));
       assertTrue(urlVal.isValid("http://www.amazon.com/test   "));
       assertTrue(urlVal.isValid("http://www.amazon.com/?a=b"));
       assertTrue(urlVal.isValid("http://www.amazon.com/#fragtest"));
       assertTrue(urlVal.isValid("http://255.255.255.255"));
       assertFalse(urlVal.isValid("http://www.amazon-.com"));
       assertFalse(urlVal.isValid("http://256.256.256.256"));
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   assert(urlVal.isValid("a://www.com"));
	   assert(urlVal.isValid("a://www.com/"));
	   assert(urlVal.isValid("a+5.-+.-://www.com"));
	   assert(urlVal.isValid("ftp://www-.com") == false);
	   assert(urlVal.isValid("ftp://-www.com") == false);
	   assert(urlVal.isValid("ftp://www.com-") == false);
	   assert(urlVal.isValid("ftp://www.-com") == false);
	   assert(urlVal.isValid("ftp://5.com"));
	   assert(urlVal.isValid("ftp://5.com.6.edu"));
	   assert(urlVal.isValid("ftp://5.org"));
	   assert(urlVal.isValid("ftp://5.net"));
	   assert(urlVal.isValid("ftp://5.co"));
	   assert(urlVal.isValid("ftp://5.5ag5.ca"));
	   assert(urlVal.isValid("ftp://www.-.com") == false);
	   assert(urlVal.isValid("ftp://www.5-s.com"));
	   assert(urlVal.isValid("ftp://ww-w.5-s.com"));
	   
	   assert(urlVal.isValid("ftp://www.5-s.com:0"));
	   assert(urlVal.isValid("ftp://www.5-s.com:0/"));
	   assert(urlVal.isValid("ftp://www.com:000"));
	   assert(urlVal.isValid("ftp://www.com:000a") == false);
	   assert(urlVal.isValid("ftp://www.com:000-") == false);
	   //assert(urlVal.isValid("ftp://w-ww.5-s.com:0000"));
	   assert(urlVal.isValid("ftp://www.com:999"));
	   //assert(urlVal.isValid("ftp://www.com:1000"));
	   
	   assert(urlVal.isValid("h://www.com:999/"));	   
	   assert(urlVal.isValid("h://www.com:999/test"));
	   assert(urlVal.isValid("h://www.com/!@#$%&*()'+=;:[]"));
	   assert(urlVal.isValid("h://www.com/!@#$%&*()'+=;:[]/"));
	   assert(urlVal.isValid("h://www.com/!@#$%&*()'+a=b;:65[]/test"));
	   assert(urlVal.isValid("h://www.com/^") == false);
	   
	   //assert(urlVal.isValid("h://www.com:999/?"));
	   //assert(urlVal.isValid("h://www.com:999/test?"));
	   //assert(urlVal.isValid("h://www.com:999/test?a=b"));
	   
	   assert(urlVal.isValid("h://www.com:999#"));	
	   assert(urlVal.isValid("h://www.com:999/#"));
	   assert(urlVal.isValid("h://www.com:999/test#"));
	   assert(urlVal.isValid("h://www.com/test"));
	   assert(urlVal.isValid("h://www.com#"));	
	   assert(urlVal.isValid("h://www.com/#"));
	   assert(urlVal.isValid("h://www.com/test#"));
	   assert(urlVal.isValid("h://www.com/test#test"));
	   assert(urlVal.isValid("h://www.com/test#//"));
   }
   
   public void testYourSecondPartition(){
	   assert(urlVal.isValid("http://0.0.0.0"));
	   assert(urlVal.isValid("http://0.0.0.") == false);
	   assert(urlVal.isValid("http://.0.0.0") == false);
	   assert(urlVal.isValid("http://0.0.0.a") == false);
	   assert(urlVal.isValid("http://a.0.0.0") == false);
	   assert(urlVal.isValid("http://0.0.a.0") == false);
	   assert(urlVal.isValid("http://255.255.255.255"));
	   //assert(urlVal.isValid("http://256.0.0.0") == false);
	   assert(urlVal.isValid("http://0.0.0.0/"));
	   
	   assert(urlVal.isValid("http://255.255.255.255:0"));
	   assert(urlVal.isValid("http://255.255.255.255:0/"));
	   assert(urlVal.isValid("http://255.255.255.255"));
	   assert(urlVal.isValid("http://255.255.255.255:000a") == false);
	   assert(urlVal.isValid("http://255.255.255.255:000-") == false);
	   //assert(urlVal.isValid("http://255.255.255.255:0000"));
	   assert(urlVal.isValid("http://255.255.255.255:999"));
	   //assert(urlVal.isValid("http://255.255.255.255:1000"));
	   assert(urlVal.isValid("http://255.255.255.255:999/"));	   
	   assert(urlVal.isValid("http://255.255.255.255:999/test"));
	   assert(urlVal.isValid("http://255.255.255.255/!@#$%&*()'+=;:[]"));
	   assert(urlVal.isValid("http://255.255.255.255/!@#$%&*()'+=;:[]/"));
	   assert(urlVal.isValid("http://255.255.255.255/!@#$%&*()'+a=b;:65[]/test"));
	   assert(urlVal.isValid("http://255.255.255.255/^") == false);
	   //assert(urlVal.isValid("http://255.255.255.255:999/?"));
	   //assert(urlVal.isValid("http://255.255.255.255:999/test?"));
	   //assert(urlVal.isValid("http://255.255.255.255:999/test?a=b"));
	   assert(urlVal.isValid("http://255.255.255.255:999#"));	
	   assert(urlVal.isValid("http://255.255.255.255:999/#"));
	   assert(urlVal.isValid("http://255.255.255.255:999/test#"));
	   assert(urlVal.isValid("http://255.255.255.255/"));
	   assert(urlVal.isValid("http://255.255.255.255/test"));
	   assert(urlVal.isValid("http://255.255.255.255#"));	
	   assert(urlVal.isValid("http://255.255.255.255/#"));
	   assert(urlVal.isValid("http://255.255.255.255/test#"));
	   assert(urlVal.isValid("http://255.255.255.255/test#test"));
	   assert(urlVal.isValid("http://255.255.255.255/test#//"));
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
    public void testAnyOtherUnitTest()
    {
        String schemeStr, authorityStr, portStr, pathStr, queryStr, url;
        boolean validURL, result;
        
        
        for (int schemeCount = 0; schemeCount < scheme.length; schemeCount++) {
            for (int authorityCount = 0; authorityCount < authority.length; authorityCount++) {
                for (int portCount = 0; portCount < port.length; portCount++) {
                    for (int pathCount = 0; pathCount < path.length; pathCount++) {
                        for (int queryCount = 0; queryCount < query.length; queryCount++) {
                            validURL = true;
                            if (!scheme[schemeCount].valid || !authority[authorityCount].valid || !port[portCount].valid
                                || !query[queryCount].valid || !query[queryCount].valid) {
                                validURL = false;
                            }
                            schemeStr = scheme[schemeCount].item;
                            authorityStr = authority[authorityCount].item;
                            portStr = port[portCount].item;
                            pathStr = path[pathCount].item;
                            queryStr = query[queryCount].item;
                            url = schemeStr + authorityStr + portStr + pathStr + queryStr;
                            
                            UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
                            result = urlVal.isValid(url);
                            
                            //assertEquals(url, validURL, result);
                            
                            if (validURL != result && printStatus) {
                                System.out.print("URL: ");
                                System.out.println(url);
                                System.out.print("Expected: ");
                                System.out.println(validURL);
                                System.out.print("Actual: ");
                                System.out.println(result);
                            }
                        }
                    }
                }
            }
        }
        
        
        
    }
    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */
    ResultPair[] scheme = {
    new ResultPair("http://", true),
    new ResultPair("http:/", false),
    new ResultPair("http:", false),
    new ResultPair("http", false),
    new ResultPair("://", false),
    new ResultPair("", false),
    };
    
    ResultPair[] authority = {
    new ResultPair("www.y.com", true),
    new ResultPair("y.org", true),
    new ResultPair("y.com", true),
    new ResultPair("y.con", true),
    new ResultPair("www.?.com", false),
    new ResultPair("y", false),
    new ResultPair("y.", false),
    new ResultPair("y.hi", false)
    };
    
    ResultPair[] port = {
    new ResultPair(":50", true),
    new ResultPair(":500", true),
    new ResultPair(":5000", true),
    new ResultPair(":50000", true),
    new ResultPair(":0", true),
    new ResultPair("", true),
    new ResultPair(":-50", false),
    new ResultPair(":abc", false),
    new ResultPair(":", false),
    new ResultPair(":500000", false),
    };
    
    ResultPair[] path = {
    new ResultPair("/thisIsAPath", true),
    new ResultPair("/?/", true),
    new ResultPair("", true),
    new ResultPair("/", true),
    new ResultPair("//", false)
    };
    
    ResultPair[] query = {
    new ResultPair("?thisIsValid", true),
    new ResultPair("?This=Is&Valid=too", true),
    new ResultPair("?This=Is&Valid=too&This=Is&Valid=too", true),
    new ResultPair("", true)
    };
    
}
