#!/usr/bin/env ruby

require 'rubygems'
require 'active_record'
require 'logger'
#
# 
#
#ActiveRecord::Base.logger = Logger.new(STDOUT) # Comment this line to turn off log output

ActiveRecord::Base.establish_connection(
  :host => 'csci403.c99q7trvwetr.us-west-2.rds.amazonaws.com',
  :username => 'mdeslis',
  :password => 'Hitsuzen13',
  :adapter => 'mysql2',
  :database => 'snacks'
)

#
# Class definitions
#
class User < ActiveRecord::Base
  def to_s
    "#{name}"
  end
end

# TODO: Your class definitions should be placed here.
class Building < ActiveRecord::Base
  has_many :machines
  def to_s
    "#{name}"
  end
end

class Machine < ActiveRecord::Base
  belongs_to :building #foreign key - building_id
  has_and_belongs_to_many :snacks
  def to_s
    "#{serial_number}"
  end
end

class Snack < ActiveRecord::Base
  has_and_belongs_to_many :machines
  def to_s
    "#{name}"
  end
end

class CreateFavorites < ActiveRecord::Migration
  def up
    create_table :favorites do |field|
      # implicit id column that is primary key
      field.string :name, :null => false
      field.text :description
      field.string :rating => 5
    end
  end

  #get rid of it when the user exits
  def down
    drop_table :favorites
  end
end

#
# Core functions.
#

#A - List Buildings
def list_buildings
  buildings = Building.all
  buildings.each do |building|
    puts "#{building} (#{building.machines.count} machines)"
  end
end

#B - List Machines
def list_machines
  machines = Machine.all 
  machines.each do |machine|
    puts "#{machine.serial_number}, #{machine.description}"
  end
end

#C - List Snacks
def list_snacks
  snacks = Snack.all 
  snacks.each do |snack|
    puts "#{snack}"
    snack.machines.each do |machine|
      puts "- #{machine.serial_number} in #{machine.building.name} Building"
    end
  end
end

#D - List Users
def list_users
  users = User.all
  users.each do |user|
    puts "#{user}"
  end
end

#E - Find a Snack
def find_snack
  puts "Candy from the trolley dear?"
  user_search = gets.chomp

  if (user_search.empty?)
    puts "Candy from the trolley dear?"
    user_search = gets.chomp
  end
  
  search_snack(user_search)
end

def search_snack(user_search)
  snack = Snack.find_by_name(user_search)

  unless snack
    puts "Sorry, the Death Eaters ate them all"
  else
    snack.machines.each do |machine|
        puts "- #{machine.serial_number} in #{machine.building.name} Building"
    end
  end
end

#F - Add a Snack
def add_snack
  puts "What concotion are you brewing?"
  add_name = gets.chomp

  if (add_name.empty?) 
    puts "What concotion are you brewing?"
    add_name = gets.chomp
  end

  puts "How would you describe it?"
  add_descrip = gets.chomp

  if (add_descrip.empty?)
    puts "How would you describe it?"
    add_descrip = gets.chomp
  end

  puts "How many calories does it have?"
  add_cal = gets.chomp

  if (add_cal.to_i < 0 || add_cal.empty?)
    puts "How many calories does it have?"
    add_cal = gets.chomp
  end

  add_machine(add_name, add_descrip, add_cal)
end

def add_machine(add_name, add_descrip, add_cal)
  puts "Choose a home for #{add_name}:"
  list_machines
  pick_machine = gets.chomp

  if (pick_machine.empty?)
    puts "Choose a home for #{add_name}:"
    list_machines
    pick_machine = gets.chomp
  end

  final_add(add_name, add_descrip, add_cal, pick_machine)
end

def final_add(add_name, add_descrip, add_cal, add_mach)
  snack = Snack.create(:name => add_name, :description => add_descrip, :calories => add_cal)
  machines = Machine.all
  machines.each do |machine|
    if (machine.serial_number == add_mach)
      snack.machines << machine
    end
  end
end


#G - Add a User
def add_user
  puts "Please input your name:"
  user_name = gets.chomp

  if (user_name.empty?) 
    puts "Please input your name:"
    user_name = gets.chomp
  end

  puts "Please input user name:"
  user_un = gets.chomp

  if (user_un.empty?)
    puts "Please input user name:"
    user_un = gets.chomp
  end

  puts "Please input user password:"
  user_pass = gets.chomp

  if (user_pass.empty?)
    puts "Please input user password:"
    user_pass = gets.chomp
  end

  users = User.create(:name => user_name,:username => user_un, :password => user_pass)
end

#H - Favorites Snacks
# def fav_snacks
#   snacks = Snack.all

#   puts "Tell us your favorite snack:"
#   pick_snack = gets.chomp

#   if (pick_snack.empty?)
#     puts "Choose a favorite snack by typing it:"
#     list_snacks
#     pick_snack = gets.chomp
#   end

#   puts "Rating #{pick_snack} (up to five *):"
#   rating = gets.chomp

#   if (rating.empty?)
#     puts "Rating #{pick_snack} (up to five *):"
#     rating = gets.chomp
#   end

#   favorites.rating << rating

#   snacks.each do |snack|
#     if (snack.name == pick_snack)
#       favorites.name << snack
#     end
#   end
# end



# TODO: Your other menu-driven functions should be placed here.

def main_menu
  puts "\nMain Menu."
  puts "A. List Buildings"
  puts "B. List Machines"
  puts "C. List Snacks"
  puts "D. List Users"
  puts "E. Find a Snack"
  puts "F. Add a New Snack"
  puts "G. Create New User"
  # puts "H. Create Favorites"
  puts "Q. Quit"
end

def execute_command(command)
  case command
  when "A", "a"
    puts "\nListing Buildings:"
    list_buildings
  when "B", "b"
    puts "\nListing Machines:"
    list_machines
  when "C", "c"
    puts "\nListing Snacks:"
    list_snacks
  when "D", "d"
    puts "\nListing Users:"
    list_users
  when "E", "e"
    puts "\nFind a Snack:"
    find_snack
  when "F", "f"
    puts "\nAdding a new Snack:"
    add_snack
  when "G", "g"
    puts "\nCreating a new User:"
    add_user
  # when "H", "h"
  #   puts "\nFavorites:"
  #   fav_snacks
  when "Q"
    puts "Exiting..."
  else
    puts "Sorry, I don't know how to do that. Too bad so sad."
  end
end

command = nil
puts "Snack Attack. Whee!"
while (command != 'Q')
  main_menu
  execute_command(command = gets.chomp!)
end