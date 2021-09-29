import sqlite3
import sys, os
import subprocess
from plum import dispatch
from numba import jit


def make():
    subprocess.run("make", shell=True)

def cleanall():
    subprocess.run("rm -rf outputs/*", shell=True)
    
def clear_previous_databases(layout:str):
    """Clears all previous databases of layout `layout`.
    """
    os.system(f"rm -f ./outputs/{layout}/*.db")
    print("Previous databases have been deleted!")

def create_temp_ini(layout:str,ncities:int,box:float,metric:str,iters:int,ntemp:int,beta_step:float):
    """Creates a temporary .ini file for a temporary configuration

    - layout: layout for city generation (circle or square)
    - ncities: number of cities generated
    - box: size of circle / square for city generation
    - metric: type of metric for distance calculation
    - ntemp: number of different temperatures to be explored
    - beta_step: increment of beta value for each temperature increase
    """

    content = f"""[DEFAULT]

[simulation]
layout = {layout}
ncities = {ncities}
box = {box}
#if circumference lbox = radius, if square lbox = side
metric = {metric}
iterations = {iters}

[simulation.temperature]
N = {ntemp}
step = {beta_step}

[outputs]
besttrip_filename = "./"

[settings]
logger_debug = true
data_debug = false
"""
    file = open("tempfile.ini","w+")
    file.write(content)
    file.close()

def remove_tempfile():
    subprocess.run("rm -f tempfile.ini", shell=True)



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

    def get_best(self):
        conn = sqlite3.connect(self.name)
        cur = conn.cursor()
        res = cur.execute("SELECT * FROM BEST")
        return list(res)

    def get_result(self,result:str):
        conn = sqlite3.connect(self.name)
        cur = conn.cursor()
        res = cur.execute(f"SELECT {result.upper()} FROM RESULTS")
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
            valids = ["PROCESSES","NCITIES","LAYOUT","BOX","METRIC","NTEMP","BETA_STEP","ITERATIONS"]
            self.settings = {}
            for i,kw in enumerate(kwargs):
                if kw.upper() not in valids:
                    raise ValueError(f"Invalid kwarg {kw} for get_record")
                if isinstance(kwargs[kw],str):
                    exec(f"self.{kw} = '{kwargs[kw]}'")
                else:
                    exec(f"self.{kw} = {kwargs[kw]}")
                self.settings[kw] = kwargs[kw]
        layout = self.settings["layout"].replace("'","")
        self.output_dir = f"./10.2/outputs/databases/"
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