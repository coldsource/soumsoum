 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';
import {TextDisplay} from '../../ui/TextDisplay.js';

export class CrewTextIndicators extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {};
		
		App.registerComponent("crew", this);
	}
	
	render() {
		if(this.state.crew===undefined)
			return null;
		
		let crew = this.state.crew;
		
		return (
			<div className="TextIndicators container">
				<TextDisplay text="O2 REGEN" type="notice" status={crew.regeneration} />
				<br /><TextDisplay text="O2 PRESSURE" type="warning" status={this.state.crew.o2_tank.dioxygen.pressure>205?"on":"off"} />
				<br /><TextDisplay text="O2 LOW" type="warning" status={this.state.crew.o2_tank.dioxygen.pressure<50?"on":"off"} />
				<br /><TextDisplay text="CO2 PRESSURE" type="warning" status={this.state.crew.co2_tank.carbon_dioxide.pressure>205?"on":"off"} />
				<br /><TextDisplay text="SUPPLIES LOW" type="warning" status={this.state.crew.supplies<500?"on":"off"} />
				<br /><TextDisplay text="WASTE HIGH" type="warning" status={this.state.crew.waste>400?"on":"off"} />
			</div>
		);
	}
}
