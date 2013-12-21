package edu.mines.rbower.internetaccessdemo;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;

/**
 * This class demonstrates network connectivity and use of the AsynchTask
 * class to keep potentially time consuming tasks off the UI thread.
 * 
 * The code in this demo is adapted from the following:
 *   http://developer.android.com/training/basics/network-ops/connecting.html
 *   http://developer.android.com/reference/android/os/AsyncTask.html
 *  
 * @author Randy Bower
 */
public class MainActivity extends Activity implements DownloadStringTask.Listener,
                                                      DownloadDocumentTask.Listener,
                                                      DownloadImageTask.Listener
{
  private TextView textView;

  @Override
  protected void onCreate( Bundle savedInstanceState )
  {
    super.onCreate( savedInstanceState );
    setContentView( R.layout.activity_main );

    // Since the TextView is used in several places, get a reference to it once.
    this.textView = (TextView)findViewById( R.id.textView );
  }

  /**
   * Callback method from the UI. Called when the "Text" button is touched.
   * 
   * @param view The view in the UI generating the callback.
   */
  public void getText( View view )
  {
    Log.d( "INTERNET ACCESS DEMO", "getText()..." );

    // Make sure there is an available network connection before starting the AsynchTask.
    ConnectivityManager connMgr = (ConnectivityManager)getSystemService( Context.CONNECTIVITY_SERVICE );
    NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
    if( networkInfo != null && networkInfo.isConnected() )
    {
      new DownloadStringTask( this ).execute( "http://eecs.mines.edu/Courses/csci498_android/test.txt" );
    }
    else
    {
      this.textView.setText( "No network connection available." );
    }
  }

  /**
   * Callback method from the DownloadStringTask class.
   * 
   * @param result The result received from the DownloadStringTask.
   */
  @Override
  public void receiveResult( String result )
  {
    Log.d( "INTERNET ACCESS DEMO", "Received string result: " + result );

    this.textView.setText( result );
  }

  /**
   * Callback method from the UI. Called when the "XML" button is touched.
   * 
   * @param view The view in the UI generating the callback.
   */
  public void getXML( View view )
  {
    Log.d( "INTERNET ACCESS DEMO", "getXML()..." );

    // Make sure there is an available network connection before starting the AsynchTask.
    ConnectivityManager connMgr = (ConnectivityManager)getSystemService( Context.CONNECTIVITY_SERVICE );
    NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
    if( networkInfo != null && networkInfo.isConnected() )
    {
      new DownloadDocumentTask( this ).execute( "http://www.ecb.int/stats/eurofxref/eurofxref-daily.xml" );
    }
    else
    {
      this.textView.setText( "No network connection available." );
    }
  }

  /**
   * Callback method from the DownloadDocumentTask class.
   * 
   * @param result The result received from the DownloadDocumentTask.
   */
  @Override
  public void receiveResult( Document result )
  {
    String exchangeRate = "USD Exchange Rate Not Found.";

    // Tidy up the XML a bit.
    result.getDocumentElement().normalize();

    // Retrieve all the <Cube> nodes. (Why are they "Cube"? Why not?!)
    NodeList itemNodes = result.getElementsByTagName( "Cube" );

    for( int i = 0; i < itemNodes.getLength(); i++ )
    {
      if( ( (Element)itemNodes.item( i ) ).getAttribute( "currency" ).equals( "USD" ) )
      {
        exchangeRate = "USD Exchange Rate: " + ( (Element)itemNodes.item( i ) ).getAttribute( "rate" );
      }
    }

    this.textView.setText( exchangeRate );

    Log.d( "INTERNET ACCESS DEMO", exchangeRate );
  }

  /**
   * Callback method from the UI. Called when the "Image" button is touched.
   * 
   * @param view The view in the UI generating the callback.
   */
  public void getImage( View view )
  {
    Log.d( "INTERNET ACCESS DEMO", "getImage()..." );

    // Make sure there is an available network connection before starting the AsynchTask.
    ConnectivityManager connMgr = (ConnectivityManager)getSystemService( Context.CONNECTIVITY_SERVICE );
    NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
    if( networkInfo != null && networkInfo.isConnected() )
    {
      new DownloadImageTask( this ).execute( "http://eecs.mines.edu/Courses/csci498_android/images/mascot.png" );
    }
    else
    {
      this.textView.setText( "No network connection available." );
    }
  }

  /**
   * Callback method from the DownloadImageTask class.
   * 
   * @param result The result received from the DownloadImageTask.
   */
  @Override
  public void receiveResult( Bitmap result )
  {
    Log.d( "INTERNET ACCESS DEMO", "Received bitmap result." );

    ( (ImageView)findViewById( R.id.imageView ) ).setImageBitmap( result );
  }
}
