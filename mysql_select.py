## Connecting to the database

## importing 'mysql.connector' as mysql for convenient
import mysql.connector as mysql
from tqdm import tqdm

## connecting to the database using 'connect()' method
## it takes 3 required parameters 'host', 'user', 'passwd'
db = mysql.connect(
    host = "192.168.14.50",
    user = "root",
    passwd = "avis@123qwe",
    database = "luce_dev"
)
print(db)

## creating an instance of 'cursor' class which is used to execute the 'SQL' statements in 'Python'
cursor = db.cursor()
## getting all the tables which are present in 'datacamp' database
cursor.execute("SHOW TABLES")
tables = cursor.fetchall() ## it returns list of tables present in the database
## showing all the tables one by one
for table in tables:
    print(table)

err_records = []
MAX_REC = 81429

## defining the Query
for i in tqdm(range(1,MAX_REC)):
    cursor.execute('SELECT cid,lac,dtype  FROM t_data WHERE id = {0}'.format(i))
    cursor.statement  #=> 'SELECT id,cid,lac,dtype FROM users WHERE id = 1'
    test_rec = cursor.fetchone()  #=> (1, 'foo')
    #print(test_rec)
    #print(i)
    is_exist = False
    query = "SELECT id FROM t_data where cid={0} and lac={1} and dtype !={2} and id > {3}".format(test_rec[0],test_rec[1],test_rec[2],i)
    #print(query)
    ## getting records from the table
    cursor.execute(query)
    ## fetching all records from the 'cursor' object
    records = cursor.fetchall()
    ## Showing the data
    for record in records:
	err_records.append(record[0])
	is_exist = True
	#print(record)

    if is_exist == True:
        err_records.append(i)


print(err_records)
if len(err_records) > 0 :
    query = "SELECT * FROM t_data where id in {0}".format(','.join(['%d'] * len(err_records)))
    print(query)
    ## getting records from the table
    cursor.execute(query, err_records)
    ## fetching all records from the 'cursor' object
    records = cursor.fetchall()
    ## Showing the data
    for record in records:
        print(record)                   

