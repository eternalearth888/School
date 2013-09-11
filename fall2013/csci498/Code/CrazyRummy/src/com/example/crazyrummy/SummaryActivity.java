package com.example.crazyrummy;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class SummaryActivity extends Activity implements OnClickListener {
	// Buttons
	Button new_game;
	Button end_game;
	
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
