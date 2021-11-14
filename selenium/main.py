from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time
import os

searchList = open(os.path.dirname(os.path.abspath(__file__))+"/searchlist.txt","r")
searchListLines = searchList.readlines()

driver = webdriver.Firefox()
for aLine in searchListLines:
    try:
        metin=aLine
        print("\nSearching: "+metin)
        #driver.get("https://www.google.com/search?q="+metin+"+site%3Ahttps%3A%2F%2Fdocs.microsoft.com&lr=lang_en")
        driver.get("https://docs.microsoft.com/en-us/search/?scope=Desktop&terms="+metin)
        time.sleep(2)
        #result = driver.find_element_by_tag_name('h3')
        result = driver.find_element_by_xpath("//h2/a")
        result.click()
        time.sleep(3)
        libName=""
        try:
            login_form = driver.find_element_by_xpath("//td[contains(.,'dll')]")
            #login_form = driver.find_element_by_xpath("//td[contains(.,'dll'")
            libName = login_form.get_attribute("innerHTML").splitlines()[0]
        except:
            libName = "not found"
        
        print("\tLibName: "+libName)
    except Exception as e: 
        print(e)

driver.close()