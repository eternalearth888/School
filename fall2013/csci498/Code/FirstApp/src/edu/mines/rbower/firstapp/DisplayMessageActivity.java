package edu.mines.rbower.firstapp;

import android.os.Bundle;
import android.app.Activity;
import android.view.MenuItem;
import android.widget.TextView;
import android.support.v4.app.NavUtils;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Intent;
import android.os.Build;

public class DisplayMessageActivity extends Activity
{
  @SuppressLint( "NewApi" )
  @Override
  protected void onCreate( Bundle savedInstanceState )
  {
    super.onCreate( savedInstanceState );
    
    // This line of code was not in the original demo - see further comments below.
    setContentView( R.layout.activity_display_message );

    // Get the message from the intent
    Intent intent = getIntent();
    String message = intent.getStringExtra( MainActivity.EXTRA_MESSAGE );

    // Create and show the text view in a blank screen, with no xml layout file.
    // TextView textView = new TextView( this );
    // textView.setTextSize( 40 );
    // textView.setText( message );

    // Set the text view as the activity layout
    // setContentView( textView );

    // The above code (from the demo) creates and shows a new TextView.
    // This code uses the view defined in the xml
    TextView textView = (TextView)findViewById( R.id.show_message );
    textView.setTextSize( 40 );
    textView.setText( message );

    // Show the Up button in the action bar.
    setupActionBar();
  }

  /**
   * Set up the {@link android.app.ActionBar}, if the API is available.
   */
  @TargetApi( Build.VERSION_CODES.HONEYCOMB )
  private void setupActionBar()
  {
    if( Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB )
    {
      getActionBar().setDisplayHomeAsUpEnabled( true );
    }
  }

  @Override
  public boolean onOptionsItemSelected( MenuItem item )
  {
    switch( item.getItemId() )
    {
      case android.R.id.home:
        // This ID represents the Home or Up button. In the case of this
        // activity, the Up button is shown. Use NavUtils to allow users
        // to navigate up one level in the application structure. For
        // more details, see the Navigation pattern on Android Design:
        //
        // http://developer.android.com/design/patterns/navigation.html#up-vs-back
        //
        NavUtils.navigateUpFromSameTask( this );
        return true;
    }
    return super.onOptionsItemSelected( item );
  }

}
