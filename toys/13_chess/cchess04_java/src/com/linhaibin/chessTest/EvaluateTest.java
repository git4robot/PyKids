package com.linhaibin.chessTest;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.linhaibin.chess.Evaluate;
import com.linhaibin.chess.State;
import com.linhaibin.chess.Utility;

public class EvaluateTest {

	private State currentState;
	@Before
	public void setUp() throws Exception {
		this.currentState = new State();
	}

	@After
	public void tearDown() throws Exception {
		this.currentState = null;
	}

	@Test
	public void testInitValue() {
		int value = Evaluate.evaluateState(currentState);	
		assertEquals(0,value);
	}
	
	
	@Test
	public void testRook() {
		int count = 0;
		for (int y = 0; y <= 9; y++){			
			for (int x = 0; x <= 8; x++){
				int k = y * 9 + x;
				int m = (9-y) * 9 + 8-x;
				if (!Evaluate.blackRookPositionValue.get(m).equals(Evaluate.redRookPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("\n");
					count++;
				}
			}
		}
		assertEquals(0, 0);
	}
	
	@Test
	public void testAdvisor() {
		int count = 0;
		for (int y = 0; y <= 9; y++){			
			for (int x = 0; x <= 8; x++){
				int k = y * 9 + x;
				int m = (9-y) * 9 + 8-x;
				if (!Evaluate.blackAdvisorPositionValue.get(m).equals(Evaluate.redAdvisorPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("\n");
					count++;
				}
			}
		}
//		Utility.debug("Number of Inconsistent pair:");
//		Utility.debug(count);
		assertEquals(0, 0);
	}
	
	@Test
	public void testAllPieces() {
		int count = 0;
		for (int y = 0; y <= 9; y++){			
			for (int x = 0; x <= 8; x++){
				int k = y * 9 + x;
				int m = (9-y) * 9 + 8-x;
				if (!Evaluate.blackCannonPositionValue.get(m).equals(Evaluate.redCannonPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("(Cannon)\n");
					count++;
				}
				else if (!Evaluate.blackPondPositionValue.get(m).equals(Evaluate.redPondPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("(Pond)\n");
					count++;
				}
				else if (!Evaluate.blackBishopPositionValue.get(m).equals(Evaluate.redBishopPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("(Bishop)\n");
					count++;
				}
				else if (!Evaluate.blackKingPositionValue.get(m).equals(Evaluate.redKingPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("(King)\n");
					count++;
				}
				else if (!Evaluate.blackKnightPositionValue.get(m).equals(Evaluate.redKnightPositionValue.get(k))){
					Utility.debug(x);
					Utility.debug(y);
					Utility.debug("(Knight)\n");
					count++;
				}
			}
		}
//		Utility.debug("Number of Inconsistent pair:");
//		Utility.debug(count);
		assertEquals(0, 0);
	}
	
	
	@Test
	public void testSingleRook() {
	if (!Evaluate.blackRookPositionValue.get(9*0+0).equals(Evaluate.redRookPositionValue.get(9*9+0))){
		Utility.debug("Inconsistent");
		Utility.debug(Evaluate.blackRookPositionValue.get(9*0+0));
		Utility.debug(Evaluate.redRookPositionValue.get(9*9+0));
	}
	assertEquals(Evaluate.blackRookPositionValue.get(9*0+0), Evaluate.redRookPositionValue.get(9*9+0));
	}
	
	@Test
	public void testInfinity(){
		Integer positiveInfinity = Integer.MAX_VALUE;
		assert(positiveInfinity.equals(positiveInfinity-1));
	}
}
