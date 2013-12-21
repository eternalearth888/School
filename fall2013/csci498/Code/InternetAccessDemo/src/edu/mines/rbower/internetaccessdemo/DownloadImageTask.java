package edu.mines.rbower.internetaccessdemo;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;

/**
 * Uses AsyncTask to create a task away from the main UI thread.
 * 
 * This task takes a URL string and uses it to create an HttpUrlConnection. Once the connection has been established,
 * the AsyncTask downloads the contents of the web page as an InputStream. Finally, the InputStream is converted into
 * a Bitmap, which is returned to the class that instantiated this task via the receiveResult callback.
 * 
 * The code in this demo is adapted from the following:
 *   http://developer.android.com/training/basics/network-ops/connecting.html
 *   http://developer.android.com/reference/android/os/AsyncTask.html
 * 
 * @author Randy Bower
 */
public class DownloadImageTask extends AsyncTask<String, Void, Bitmap>
{
  private Listener listener;

  public interface Listener
  {
    public void receiveResult( Bitmap result );
  }

  public DownloadImageTask( Listener listener )
  {
    super();
    this.listener = listener;
  }

  @Override
  protected Bitmap doInBackground( String... urls )
  {
    // urls comes from the execute() call: urls[ 0 ] is the url to download.
    try
    {
      return downloadUrl( urls[0] );
    }
    catch( IOException e )
    {
      Log.e( "INTERNET ACCESS DEMO", "Unable to retrieve web page. URL may be invalid." );
      return null;
    }
  }

  // onPostExecute receives the results of the AsyncTask on the UI thread.
  @Override
  protected void onPostExecute( Bitmap result )
  {
    this.listener.receiveResult( result );
  }

  // Given a URL, establishes an HttpUrlConnection and retrieves the web page content as a InputStream.
  // The contents of the stream are then returned as a Bitmap.
  private Bitmap downloadUrl( String myurl ) throws IOException
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

      // Convert the InputStream into a Document
      return readImage( input );
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

  // Reads an InputStream and converts it to a Bitmap.
  private Bitmap readImage( InputStream stream )
  {
    return BitmapFactory.decodeStream( stream );
  }
}
