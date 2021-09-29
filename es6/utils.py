import subprocess
import sqlite3
import sys, os

def clean():
    subprocess.run("make clean", shell=True)
    print("Cleaned previous outputs with make.")

def create_temp_ini(temperature,spins,j,h,metro,runs,blocks):
    content = f"""[DEFAULT]

[simulation]
runs = {runs}
nblocks = {blocks}
temperature = {temperature}
n_spin = {spins}
j = {j}
h = {h}
metro = {metro}

[settings]
logger_debug = true
data_debug = false
"""
    file = open("tempfile.ini","w+")
    file.write(content)
    file.close()


class Container:
    """
    Class to merge database query results and database name
    """
    def __init__(self,name:str,data:tuple):
        if name is None or data is None:
            raise ValueError("Invalid init argument passed for container")
        self.name = name
        self.data = data

    def __string__(self):
        return str(self.name)+"-->\t"+str(self.data)
    
    def __repr__(self):
        return str(self.name)+"-->\t"+str(self.data)

    def get_variable(self,variable:str):
        conn = sqlite3.connect(self.name)
        cur = conn.cursor()
        res = cur.execute(f"SELECT * FROM {variable.upper()}")
        return list(res)

    def get_name(self):
        return self.name
    
    def get_data(self):
        return self.data



class DatabaseHandler():
    """
    Class that reads the sqlite3 database written from the simulation
    """
    def __init__(self,*args,**kwargs):
        if len(kwargs)>0:
            assert len(args)==0,"Cannot pass args and kwargs simulaneously"
        if len(args)>0: 
            assert len(kwargs)==0,"Cannot pass args and kwargs simulaneously"
            if not isinstance(args,dict):
                "Args must be a dict for record types"
        if len(args)>0:
            self.__init__(**args[0])
        else:
            valids = ["TEMP","BETA","NSPIN","J","H","SAMPLING","NSTEPS","BLOCKS"]
            self.settings = {}
            for i,kw in enumerate(kwargs):
                if kw.upper() not in valids:
                    raise ValueError(f"Invalid kwarg {kw} for get_record")
                if isinstance(kwargs[kw],str):
                    exec(f"self.{kw} = '{kwargs[kw]}'")
                else:
                    exec(f"self.{kw} = {kwargs[kw]}")
                self.settings[kw] = kwargs[kw]
        self.output_dir = f"./outputs/databases/"
        self.keys = ["id"]+[v.lower() for v in valids]
    
    def __get_settings_sql(self):
        sql = "SELECT * FROM SETTINGS WHERE "
        for i,key in enumerate(self.settings):
            if isinstance(self.settings[key],str):
                sql += f"{key} = '{self.settings[key]}'"
            else:
                sql += f"{key} = {self.settings[key]}"
            if i < len(self.settings)-1:
                sql += " AND "
        return sql
    
    def __repr__(self):
        string = "--> SETTINGS:\t"
        for i,s in enumerate(self.settings):
            string += f"{s} - {self.settings[s]}"
            if (i<len(self.settings)-1):
                string += ",  "
        return string
    
    def __str__(self):
        string = "--> SETTINGS:\t"
        for i,s in enumerate(self.settings):
            string += f"{s} - {self.settings[s]}"
            if (i<len(self.settings)-1):
                string += ",  "
        return string

    def get_setting_value(self,value:str):
        try:
            return self.settings[value]
        except Exception as e:
            print(f"Could not get setting: {value}")

    def search(self,debug=True):
        sql = self.__get_settings_sql()
        results = []
        for file in sorted(os.listdir(self.output_dir)):
            if file.endswith(".db"):
                conn = sqlite3.connect(self.output_dir+file)
                cursor = conn.cursor()
                x = list(cursor.execute(sql))
                if len(x)>0:
                    if debug: print("--> ",list(cursor.execute("PRAGMA database_list;"))[0])
                    data = x[0]
                    assert len(self.keys)==len(data)
                    d = {}
                    for i in range(len(data)):
                        d[self.keys[i]] = data[i]
                    c = Container(name=self.output_dir+file,data=d)
                    results.append(c)
                conn.close()
        return results