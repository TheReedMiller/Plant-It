<h1>Plant-It</h1>
<img width="1000" alt="Screenshot 2025-05-12 at 9 17 46 PM" src="https://github.com/user-attachments/assets/ce774877-9c59-4051-be7c-956d80bd839c" />

<h2>About Plant It</h1>
<p>Plant It is an interactive Task Manager that combines a simple 'To-do-list' with a fun, interactive game. My goal was to make a full scale application using C++ and CMake,
that my friends, family and I, could download and use. This project was a carefully crafted balance between a profesional task manager tool, and a fun 'retro-style' video game. 
This application is comprised of two main components: the <b>Game</b> and the <b>Task Manager. Some of the important functionality is highlighted below, but important controls and info
can be found within the application within the help or about menu bar options.</b> </p>

# How to Use!!?
This program was developed using a MAC, so currently this version will only work on a MAC. There is a provided executable that you can dowload and use at your leisure. If I have free time in between projects I hope one day to make this program available for Windows as well (I'm too busy to add one for Linux..)

There are two Zip files that you can download and extract a working Plant-It executable. One is a Demo, which makes shows the entirety of the application, but without the need to wait (as waiting for plants to get dry and change state takes a while). The other is a regular version, this is the intented version of the application that you can use to keep track of tasks, and water plants, this version DOES have lots of waiting. If you're interested in breifly trying the code for yourself, try the Demo!

<h3>About the Game</h3>
<p>Within the game, you can purchase, sell, move, display and collect various types of plants, each with different functionality and gameplay. The goal is to collect plants and 
customize your garden to your own desires. Plants can be purchased via a menu in the menu bar. Of course you'll need to pay for these plants, so the game has its very own banking system.
As shown within the top right corner of the Plant-It window, there is a bank with a displayed amount of 'Plant Coins'. Each plant has a varying cost that is displayed within the menu bar
selector. How do you get 'Plant Coins' to pay for these plants? Why, by completing tasks of course!</p>
<img width="267" alt="Screenshot 2025-05-12 at 9 38 45 PM" src="https://github.com/user-attachments/assets/fac415a0-51f8-45c1-90b7-228a46db460b" />

<img width="165" alt="Screenshot 2025-05-12 at 9 40 10 PM" src="https://github.com/user-attachments/assets/341da4be-2b14-4ea4-8a32-3415b5b39615" />
<h3>About the Task Manager</h3>
<p>The Task Manager is the view on the right side of the screen, it is repsonsible for organizing and managing the given tasks within this application. To add a new task you simply select
the 'Add Task' menu bar option. When a new task is created, or when an existing task is selected to edit(right-click), the user is presented with a custom dialog box(shown below) to edit
both the difficulty and description of the task. The description is the text that aprears on each task item. The difficulty changes both the color of the circle on each task, as well as
the amount of coins received when completed. The difficulty can be either Easy, Moderate and Hard. Tasks can be completed by double clicking them, this results in a reward of 'Plant Coins'
as well as the completed task displaying a lighter color, and a green check mark within the top left corner. Tasks can be dragged and moved, as well as deleted as the user desires.</p>

<p>Not shown in the imaged provided, this task manager has many detailed algorithms to help add fluidity to movement, deletion and placement of tasks. When tasks are deleted, new tasks will automatically take there place. When tasks are picked up and dragged, they will automatically snap back into place.</p>
<img width="150" alt="Screenshot 2025-05-12 at 10 00 32 PM" src="https://github.com/user-attachments/assets/25368fe5-d105-49bf-b47d-d9e0de84d2fb" />

# Watering the Plants
On top of being able to purchase and place plants, there is actually some 'Plant-Like" functionality to this task manager. After a certain period of time, each individual plant will change its image to a 'Dry' state. This will encourage users to use a 'Watering Can' object that can be double-clicked, to water the plants and return them back to their original state. This feature adds both animation and states for both the Plants and the Watering Can objects. Images below show thie functionality in action.

<img width="600" alt="Screenshot 2025-05-23 at 12 13 53 PM" src="https://github.com/user-attachments/assets/9daf002a-dded-45a2-a58f-52f2b8737925" />
<img width="600" alt="Screenshot 2025-05-23 at 12 13 58 PM 1" src="https://github.com/user-attachments/assets/c55af1bf-5546-4da2-a7aa-f570d48f1724" />

# Fertilizing Plants
I wanted this to be a 'Task Manager' more than a game that takes away your focus. To promote users to get tasks done, spend more time working elsewhere, and spend less time actively focused on 'Plant-It' itself, I intruduced the ability to fertilize plants! Within the Plant menu option, fertilizer can be bought. Upon dragging and releasing the fertilizer on a plant, the plant will consume the fertilizer. In turn, the 'fertilized plant' will take longer to become dry. This allows for the user to worry less about watering their plants, while still enjoying the realistic functionality of the plants. Images of this functionality can be seen below.

<img width="600" alt="Screenshot 2025-05-31 at 12 32 12 PM" src="https://github.com/user-attachments/assets/9e2f4ac3-3f28-4ffa-835f-7b2f9bab555a" />
<img width="200" alt="Screenshot 2025-05-31 at 12 32 24 PM" src="https://github.com/user-attachments/assets/d54f9c47-990e-4df1-8b37-d71fde7ad573" />


# Tech Stack
This Project is a C++ project, that makes use of CMake, wxWidgets and XML. While these may not be state of the art in todays world, I wanted to make use of the tools presented to me 
during my undergraduate studies, these being some of those tools. 

# Object Oriented Programming Style
One of my largest goals for this project was to use a detailed Object Oreiented Programming style. This resulted in me seperating each component within this application  into its own 
seperate class, with functionality within them all. For example, all of this is contained within an App class, the App has two views: GameView and TaskView. Each of those views contain 
the Game Object and Task Manager Object respectidly. The Game Class contains a vector of items, which trough class inheritence and polymorphism, contains a collection of a variety of plants.
Below you can see a short list of just some of the many classes used within this application.
<ul>
  <li>PlantItApp</li>
  <li>GameView</li>
  <li>TaskView</li>
  <li>Game</li>
  <li>TaskManager</li>
  <li>TaskDlgBox</li>
  <li>Task</li>
  <li>Item</li>
  <li>Plant</li>
  <li>SunFlower</li>
  <li>Rose</li>
  <li>Bank</li>
</ul>

# XML Saving and Loading
Another important goal within this project, was for the user to be able to save and load current/previous progress. This was done though creation and reading of an XML document. By
simply selecting either the save/load file-menu option. The application can save/load each item, plant, task and more within the game. Ensuring that when the game is loaded, it is in 
the exact same state as you left it, and can continue where you left off last time. A short example of what that XML file would look like is shown below(Note: this is just an example, all editable attributes of this task manager are saved).

<img width="555" alt="Screenshot 2025-05-23 at 11 43 51 AM" src="https://github.com/user-attachments/assets/5bdbfad4-3276-4413-a2f9-cdb1b87a51bd" />

# What I Learned
This Project focused on two main obectives: Object Oriented Programming and Professional Development. This project was a perfect example of both. I worked hard to plan ahead of time the
structure and design of this application. Making sure that each desired functionality was reflected within a class in the program. 

# AI Generated Images
I would like to note, that the images used within this project were all generated from ChatGPT. While I can guerentee no ChatGPT or AI generation was used within the code of this project.
I am far from a graphic designer, so I was perfectly confortable letting ChatGPT lend me a hand, and save me countless hours worth of art creation.
