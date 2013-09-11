package com.example.crazyrummy;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

/**
 * Description: This is the activity that runs when the user decides to end the game .
 * It will show the players and their final scores and will give the user the option
 * of creating a new game or ending the game all together. 
 * 
 * Document Statement: The Class SummaryActivity.
 * 
 * @author: Maria Deslis
 */
public class SummaryActivity extends Activity implements OnClickListener {
	// Buttons
	/** The new_game. */
	Button new_game;
	
	/** The end_game. */
	Button end_game;
	

	/**
	 * This method implements OnClickListener Interface and defines our objects.
	 * 
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 * 
	 * @param savedInstanceState Bundle
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		setContentView(R.layout.activity_summary);
		super.onCreate(savedInstanceState);
		
		new_game=(Button)findViewById(R.id.new_game);
		end_game=(Button)findViewById(R.id.end_game);
		
		new_game.setOnClickListener(this);
		end_game.setOnClickListener(this);
		
		Intent intent = getIntent();
		String p1score = intent.getStringExtra(MainActivity.p1_score);
		String p2score = intent.getStringExtra(MainActivity.p2_score);
		String p3score = intent.getStringExtra(MainActivity.p3_score);
		
		TextView final_p1_score = (TextView)findViewById(R.id.player_1_score);
		TextView final_p2_score = (TextView)findViewById(R.id.player_2_score);
		TextView final_p3_score = (TextView)findViewById(R.id.player_3_score);
		
		final_p1_score.setText(p1score);
		final_p2_score.setText(p2score);
		final_p3_score.setText(p3score);
	}

	/**
	 * This method creates options menu/activity bar in the activity
	 * 
	 * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
	 * 
	 * @param menu Menu
	 */
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	/**
	 * This method tells the activity what to do when certain buttons are pushed
	 * 
	 * @see android.view.View.OnClickListener#onClick(android.view.View)
	 * 
	 * @param v View
	 */
	@Override
	public void onClick(View v) {
		if( v== new_game) {
			Intent prev_act = new Intent(this, MainActivity.class);
			startActivity(prev_act);
			finish();
		}
		if (v == end_game) {
			this.finish();
		}

	}
}
