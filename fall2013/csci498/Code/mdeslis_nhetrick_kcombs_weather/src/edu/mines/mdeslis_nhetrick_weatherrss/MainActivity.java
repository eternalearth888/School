package edu.mines.mdeslis_nhetrick_weatherrss;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.TextView;

/**
 * 
 * @author earth
 * Weather app that uses Yahoo RSS feed for weather
 * Pair Programing with Kira Combs, Nicola Hetrick and Maria Deslis
 * 
 */

public class MainActivity extends Activity implements DownloadDocumentTask.Listener {

	private TextView textView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		// Since the TextView is used in several places, get a reference to it once.
	    this.textView = (TextView)findViewById( R.id.info );
	    
	    // Call getXML
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	//Grab XML file
	public void getXML(View v) {
		Log.d("My Weather", "getXML()...");
		
		//Check that there is an available network connection before starting the AsynchTask
		ConnectivityManager connMgr = (ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
		
		if (networkInfo != null && networkInfo.isConnected()) {
			new DownloadDocumentTask(this).execute("http://weather.yahooapis.com/forecastrss?z=80401");
		} else {
			this.textView.setText("No network connection available");
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
	    String goldenWeather = "Weather not found.";

	    // Tidy up the XML a bit.
	    result.getDocumentElement().normalize();

	    // Retrieve all the <Cube> nodes. (Why are they "Cube"? Why not?!)
	    NodeList itemNodes = result.getElementsByTagName( "yweather:forecast" );

	    for( int i = 0; i < itemNodes.getLength(); i++ )
	    {
	      if( ( (Element)itemNodes.item( i ) ).getAttribute( "day" ).equals( "Fri" ) )
	      {
	        goldenWeather = "Current Weather: " + ( (Element)itemNodes.item( i ) ).getAttribute( "text" );
	      }
	    }

	    this.textView.setText( goldenWeather );

	    Log.d( "My Weather", goldenWeather );
	  }

}
