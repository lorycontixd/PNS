import sqlite3
import sys, os
from plum import dispatch
from numba import jit



    
def clear_previous_databases(layout:str):
    """Clears all previous databases of layout `layout`.
    """
    os.system(f"rm -f ./outputs/{layout}/*.db")


def create_temp_ini(layout:str,ncities:int,box:float,metric:str,nind:int,npop:int,fpi:bool=True):
    """Creates a temporary .ini file for a temporary configuration

    - layout: layout for city generation (circle or square)
    - ncities: number of cities generated
    - box: size of circle / square for city generation
    - metric: type of metric for distance calculation
    - nind: number of individuals for each population
    - npop: number of popuations at which the simulation is stopped
    """

    content = f"""[DEFAULT]

[simulation]
layout = {layout}
ncities = {ncities}
box = {box}
#if circumference lbox = radius, if square lbox = side
metric = {metric}

[simulation.individuals]
N = {nind}

[simulation.population]
N = {npop}

[outputs]
besttrip_filename = "./"

[settings]
logger_debug = true
data_debug = false
fitness_per_iteration = {fpi}

[settings.database]
active = true
remove_previous = false
#name = ... (if not autoupdate)
debug = false
"""
    file = open("tempfile.ini","w+")
    file.write(content)
    file.close()



class DatabaseReader():
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
            valids = ["NCITIES","LAYOUT","BOX","METRIC","MAX_IND","MAX_POP"]
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
        self.con = sqlite3.connect(f"outputs/{layout}/results.db")
        self.cur = self.con.cursor()
        
    def settings_select(self):
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
    

    @dispatch
    def get_setting(self,index:int):
        setting = list(self.cur.execute("SELECT * FROM SETTINGS"))[index]
        return setting
    
    @dispatch
    def get_setting(self):
        index = next(row[0] for row in self.cur.execute(self.settings_select()))
        return index
    
    @dispatch
    def get_fpi(self,index:int):
        fpi = list(self.cur.execute("SELECT * FROM FPI"))[index]
        return fpi
    
    @dispatch
    def get_fpi(self):
        index = self.get_setting()
        fpi = self.get_fpi(index)
        return fpi
    
    @dispatch
    def get_fitness(self,index:int):
        fitness = list(self.cur.execute("SELECT * FROM FITNESS"))[index]
        return fitness[0]
    
    @dispatch
    def get_fitness(self):
        fitness = self.get_fitness(self.get_setting())
        return fitness[0]

    @dispatch
    def get_best(self,index):
        best = list(self.cur.execute("SELECT * FROM BEST"))[index]
        return list(best)
    
    @dispatch
    def get_best(self):
        index = self.get_setting()
        best = self.get_best(index)
        return list(best)