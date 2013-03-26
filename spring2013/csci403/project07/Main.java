/*
 * MARIA DESLIS
 * BAKOS - CSCI403
 * SPRING 2013
 * PROJECT07
 *
 */
  
import java.sql.*;
import javax.sql.*;
import java.sql.PreparedStatement;
import java.util.*;

public class Main {

  public static void main(String[] args) {
    Main run = new Main();

    run.select();
  }

  public void select() {
    // Print the starting statements
    System.out.println("Database connectivity test wants to battle!");

    // Strings for connecting to the MySQL server remotely
    String driver = "com.mysql.jdbc.Driver";
    String hostName = "csci403.c99q7trvwetr.us-west-2.rds.amazonaws.com";
    String url = "jdbc:mysql://" + hostName + ":3306/snacks";

    // Making sure it's me who connects and no one else
    String username = "mdeslis";
    String password = "Hitsuzen13";

    // DML command required for this project07
    String dmlCommand = "SELECT name FROM project_test";

    // Print connecting statements
    System.out.println("I choose you, snacks!");
    try 
    {
      // Connect to the database
      Class.forName(driver);
      Connection conn = DriverManager.getConnection(url, username, password);
      Statement stmt = conn.createStatement();
      ResultSet results = stmt.executeQuery(dmlCommand);

      // Print that the connection was successful
      System.out.println("snacks used 'SELECT name FROM project_test;' !");
      System.out.println();
	
      // Iterate through table and retrieve results
      while(results.next()) 
      {
        System.out.println(results.getString("name"));
      }

      System.out.println();

      // Close results, statements, and connections
      results.close();
      stmt.close();
      conn.close();

      // Print exiting statements
      System.out.println("It's super effective!!");
      System.out.println("Snacks wins! Battle over!");
    } 

    // Error Checking

    // Driver Not Found
    catch (ClassNotFoundException e) 
    {
      System.out.println("Could not load SQLite JDBC Driver.");
      System.out.println(e.getMessage());
    } 
    // SQL Error
    catch (SQLException e) 
    {
      System.out.println("SQL Error.");
      System.out.println(e.getMessage());
    }
    // Everything else
    catch (Exception e) 
    {
      System.out.println("Error.");
      System.out.println(e.getMessage());
    }
  }
}
