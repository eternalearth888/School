package edu.mines.rbower.internetaccessdemo;

import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

import android.os.AsyncTask;
import android.util.Log;

/**
 * Uses AsyncTask to create a task away from the main UI thread.
 * 
 * This task takes a URL string and uses it to create an HttpUrlConnection. Once the connection has been established,
 * the AsyncTask downloads the contents of the web page as an InputStream. Finally, the InputStream is converted into
 * a String, which is returned to the class that instantiated this task via the receiveResult callback.
 * 
 * The code in this demo is adapted from the following:
 *   http://developer.android.com/training/basics/network-ops/connecting.html
 *   http://developer.android.com/reference/android/os/AsyncTask.html
 * 
 * @author Randy Bower
 */
public class DownloadStringTask extends AsyncTask<String, Void, String>
{
  private Listener listener;

  public interface Listener
  {
    public void receiveResult( String result );
  }

  public DownloadStringTask( DownloadStringTask.Listener listener )
  {
    super();
    this.listener = listener;
  }

  @Override
  protected String doInBackground( String... urls )
  {
    // urls comes from the execute() call: urls[ 0 ] is the url to download.
    try
    {
      return downloadUrl( urls[0] );
    }
    catch( IOException e )
    {
      return "Unable to retrieve web page. URL may be invalid.";
    }
  }

  // onPostExecute receives the results of the AsyncTask on the UI thread.
  @Override
  protected void onPostExecute( String result )
  {
    this.listener.receiveResult( result );
  }

  // Given a URL, establishes an HttpUrlConnection and retrieves the web page content as a InputStream.
  // The contents of the stream are then returned as a String.
  private String downloadUrl( String myurl ) throws IOException
  {
    InputStream input = null;
    try
    {
      URL url = new URL( myurl );
      HttpURLConnection conn = (HttpURLConnection)url.openConnection();
      conn.setReadTimeout( 10000 );  // milliseconds
      conn.setConnectTimeout( 15000 );  // milliseconds
      conn.setRequestMethod( "GET" );
      conn.setDoInput( true );

      // Starts the query
      conn.connect();
      int response = conn.getResponseCode();
      Log.d( "INTERNET ACCESS DEMO", "The response is: " + response );
      input = conn.getInputStream();

      // Convert the InputStream into a string
      return readString( input );
    }
    // Makes sure that the InputStream is closed after the app is finished using it.
    finally
    {
      if( input != null )
      {
        input.close();
      }
    }
  }

  // Reads an InputStream and converts it to a String.
  private String readString( InputStream stream ) throws IOException, UnsupportedEncodingException
  {
    Scanner scan = new Scanner( stream );
    StringBuilder sb = new StringBuilder();
    while( scan.hasNextLine() )
    {
      sb.append( scan.nextLine() );
      sb.append( "\n" );
    }
    return sb.toString();
  }
}
