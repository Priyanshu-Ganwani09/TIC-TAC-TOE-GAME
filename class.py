import requests
import http.client
import json  

class AMZPR:
    def  __init__(self):
       print("inside a constructor")
    def input_menu(self):
        user_input=input("""how would i help you regariding prodcut.\n
                            press 1. To know about product information.\n
                            press 2. To exit the system.
                         
                        """)
        
        if user_input=="1":
            self.p2_inform_data()
        
        elif user_input=="2":
            print("Thanks for visiting the Amazone product inform system ")

    def p2_inform_data(self):

        n1=str(input("please enter the asin id of the speicific product"))
        self.fetch_asin(n1)

    def fetch_asin(self,n1):

        url = "https://real-time-amazon-data.p.rapidapi.com/product-details"
        querystring = ({"asin":n1,"country":"US",})

        headers = {"x-rapidapi-key": "f57bd19b2dmsh864dc229b458397p1dfd77jsnd18fd8a014f1","x-rapidapi-host": "real-time-amazon-data.p.rapidapi.com"}
        response1 = requests.get(url, headers=headers, params=querystring)

        response=response1.json()
        self.product_cat(response)

    def product_cat(self,response):

        self.u2_input=input("""select the prodcut detail to sepecify:-\n
                            1. Press 1 for Genral information of product. \n
                            2. Press 2 for Exact inforation about the product.\n
                            3. Press 3 for product images and url link.\n
                            4. Press 4 for product stats.\n
                            5. Press 5 for stats.
              """)

        if self.u2_input=="1":
            a1=["has_aplus","has_brandstory","has_video","is_amazon_choice","is_best_seller","is_prime"]
            result1 = [] 

            for i in a1:
                r1 = response['data'].get(i) 
                result1.append(f"product {i} = {r1}") 

            print("\n".join(result1))
            self.product_cat(response)

        elif self.u2_input=="2":
            result2 = []
            r2 = response['data'].get("about_product")
            result2.append(str(r2)) 

            print("\n".join(result2))

            print(response['data'].get("product_description"),end="\n")
            print(response['data'].get("product_information"),end="\n" )

            self.product_cat(response)

        elif self.u2_input=="3":
        
            a3=["product_byline_link", "product_photo","product_url"]
            result3 = [] 

            for i in a3:
                r3 = response['data'].get(i) 
                result3.append(f" {i} = {r3}") 

            print("\n".join(result3))

            self.product_cat(response)
        
        
        elif self.u2_input=="4":
            a4 = ["product_original_price","product_price","product_price_max","product_num_offers","product_star_rating"]
            result4=[]
            for i in a4: 
                r4 = response['data'].get(i) 
                result4.append(f"{i} = {r4}") 
                
            print("\n".join(result4))

            self.product_cat(response)
            
        elif self.u2_input=="5":
            print("exit")

    def product(self):

        print("product quantity 140396 ")
        print("product country US")

class dealer(AMZPR):
    def product(self):
        self.product_requirement="10 US dollar"
        super().product()
        print(self.product_requirement)

class seller(dealer):
    pass
