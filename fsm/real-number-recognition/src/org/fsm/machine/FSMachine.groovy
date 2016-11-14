package org.fsm.machine

import org.fsm.entity.Alpha
import org.fsm.entity.State

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMachine {
    State currentState
    FSMConfig fsm

    // dunno if needed
    Alpha lastConsumedCharcter

    public FSMachine(currentState, config) {
        this.currentState = currentState
        this.fsm = config
    }

    public List feedChar(CharSequence aChar) {
        try {
            Alpha a = this.fsm.alphabet.converCharToAlpha(aChar)
            this.lastConsumedCharcter = a
            return this.fsm.transitionList.find { it.from == this.currentState }.possibleMoves.findAll { it.alpha == a }
        } catch(Exception ex) {
            println ex.toString()
        }
    }
}
