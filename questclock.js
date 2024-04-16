const {MongoClient} = require('mongodb');
const {express} = require('express');
const {cors} = require('cors');

const uri = "mongodb+srv://Team65:ka1o40V2jAj4SstC@questclock.ofavxyx.mongodb.net/?retryWrites=true&w=majority&appName=QuestClock";
const client = new MongoClient(uri);

client.connect();
const database = client.db("QuestClockLogin");
const collection = database.collection("users");

async function login()
{
    try
    {
        try
        {
            const finduser = await collection.findOne({username: "Brian", password: "Brian123"});
            if (finduser == null)
            {
                console.log('login failed, username and/or password may be incorrect \n');
            }
            else
            {
                console.log(`login successful ${JSON.stringify(finduser)} \n`);
            }
        }
        catch(e)
        {
            console.error(`something went wrong with login: ${e}\n`);
        }
    }
    catch(e)
    {
        console.error(e);
    }
    finally
    {
        await client.close();
    }
};

/*using to allow manager to add tasks to employees, currently changes their role but we can change it*/
async function AddTask(){
    try{
        const findUser = await collection.find({username: "Brian", role: "Manager" })
        if(findUser == null){
            console.log('Access Denied \n');
        }

        else{
           /* check if employee exists*/
            const findEmployee = await collection.findOne({username: "Jim", role: "employee"});
            if(findEmployee == null){
                console.log('Employee not found \n');
            }
            else{
                try{
                /*change task of user */
                const filter = {username: "Jim"};
                const updateEmployee = {
                    $set: {
                        role: "manager",
                    },
                };
                const result = await collection.updateOne(filter, updateEmployee);
                }
                catch(e){
                    console.log('could not update user: ${e}\n');

                }
               
            }
        }
    }

    catch(e){
        console.error(`something went wrong with accessing: ${e}\n`);
    }
    finally{
        await client.close();
    }
};

//use to find users - can specify parameters later
//change to boolean
async function FindUser(){
    try
    {
        try
        {
            const finduser = await collection.findOne({username: "Brian", password: "Brian123"});
            if (finduser == null)
            {
                console.log('login failed, username and/or password may be incorrect \n');
            }
            else
            {
                console.log(`login successful ${JSON.stringify(finduser)} \n`);
            }
        }
        catch(e)
        {
            console.error(`something went wrong with login: ${e}\n`);
        }
    }
    catch(e)
    {
        console.error(e);
    }
    finally
    {
        await client.close();
    }
}

async function createuser()
{
    try 
    {
        const user = 
        {
            username: "Brian",
            password: "Brian123",
            role: "Manager",
        };

        try 
        {
            await collection.insertOne(user);
            console.log(`user successfully inserted.\n`);
        } 
        catch (e) 
        {
            console.error(`Something went wrong trying to create the new user: ${e}\n`);
        }

    }
    catch(e) 
    {
        console.error(e);
    }
    finally 
    {
        await client.close();
    }
};


//createuser().catch(console.error);
AddTask().catch(console.error);
//login().catch(console.error);