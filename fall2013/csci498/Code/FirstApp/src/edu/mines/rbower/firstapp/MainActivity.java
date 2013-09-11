package edu.mines.rbower.firstapp;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends Activity
{
  public final static String EXTRA_MESSAGE = "edu.mines.rbower.firstapp.MESSAGE";

  @Override
  protected void onCreate( Bundle savedInstanceState )
  {
    super.onCreate( savedInstanceState );
    setContentView( R.layout.activity_main );
  }

  @Override
  public boolean onCreateOptionsMenu( Menu menu )
  {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate( R.menu.main, menu );
    return true;
  }

  /**
   * Called when the user clicks the Send button.
   *
   * @param view The Send button on the main activity screen.
   */
  public void sendMessage( View view )
  {
    /*
     * An Intent is an object that provides runtime binding between separate components (such as two activities).
     * The Intent represents an app’s "intent to do something." You can use intents for a wide variety of tasks,
     * but most often they’re used to start another activity.
     */

    // Get a new Intent object with this activity as the context and DisplayMessageActivity as the target.
    Intent intent = new Intent( this, DisplayMessageActivity.class );

    // Find the EditText view and get the text in it.
    EditText editText = (EditText)findViewById( R.id.edit_message );
    String message = editText.getText().toString();

    // Put the message into the intent object and launch the intent.
    intent.putExtra( EXTRA_MESSAGE, message );
    startActivity( intent );
  }

    @Override
  protected void onResume()
  {
    super.onResume(); // Must do this or app will crash!

    // Get the Shared Preferences object.
    SharedPreferences sharedPrefs = this.getPreferences( Context.MODE_PRIVATE );

    // The second parameter to getString is the default to use if nothing exists.
    String savedMessage = sharedPrefs.getString( EXTRA_MESSAGE, "" );

    // Find the EditText view and set the text to the saved value.
    EditText editText = (EditText)findViewById( R.id.edit_message );
    editText.setText( savedMessage );

    // Show a log message so we'll know this worked.
    Log.d( "FIRST_APP", "\"" + savedMessage + "\" retrieved from shared preferences." );

    // An alternate way to do all this on one line ... is it better?
    // ( (EditText)findViewById( R.id.edit_message ) ).setText( sharedPrefs.getString( EXTRA_MESSAGE, "" ) );
  }

  @Override
  protected void onPause()
  {
    super.onPause(); // Must do this or app will crash!

    // Find the EditText view and get the text currently in it.
    String messageToSave = ( (EditText)findViewById( R.id.edit_message ) ).getText().toString();

    // Get the Shared Preferences object.
    SharedPreferences sharedPref = this.getPreferences( Context.MODE_PRIVATE );

    // Get a Shared Preferences Editor object.
    SharedPreferences.Editor editor = sharedPref.edit();

    // Tell the editor object to save the string and then commit the change.
    editor.putString( EXTRA_MESSAGE, messageToSave );
    editor.commit();

    // Show a log message so we'll know this worked.
    Log.d( "FIRST_APP", "\"" + messageToSave + "\" saved to shared preferences." );
  }
}
