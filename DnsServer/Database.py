import pandas as pd

"""
Database framework:
- Header: ip of computer
- Online: if the node is connected to the network
- Last connection: last time that the node was connected

"""

class Database(object):
    def __init__(self, fileRoute):
        self.fileRoute = fileRoute
        
        #self.data = pd.DataFrame(columns=["Header", "online", "last_connection"])
        self.data = pd.read_csv(self.fileRoute)
    
    def test(self):
        self.data.loc[len(self.data)] = [len(self.data), "http://localhost:5000", False, None]
        
    def add(self):
        pass
        
    def getAll(self):
        return self.data.values
        
    def fetch(self, ip):
        ip_list = self.data["Header"].values
        if ip in ip_list:
            return True, self.data.loc[self.data.Header == ip, "Online"]

    def save(self):
        self.data.to_csv(self.fileRoute, index=False)
