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

export class CrewControl extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.toggleRegeneration = this.toggleRegeneration.bind(this);
		
		App.registerComponent("crew", this);
	}
	
	toggleRegeneration() {
		if(this.state.crew.regeneration=="on")
			App.api.command({component: "crew", action: "regeneration_off"});
		else
			App.api.command({component: "crew", action: "regeneration_on"});
	}
	
	render() {
		if(this.state.crew===undefined)
			return null;
		
		const crew = this.state.crew;
		return (
			<div className="CrewControl container">
				<div className="legend">Crew control</div>
				<div>
					<span onClick={() => App.api.command({component: "crew", action: "empty_waste"})} className="fa fa-arrow-left"></span>
					&#160;Empty waste
				</div>
				<div>
					<span onClick={() => App.api.command({component: "crew", action: "empty_co2"})} className="fa fa-arrow-left"></span>
					&#160;Empty CO2
				</div>
				<div>
					<span onClick={this.toggleRegeneration} className={crew.regeneration=="on"?"fa fa-toggle-on":"fa fa-toggle-off"}></span>
					&#160;O2 Regeneration
				</div>
			</div>
		);
	}
}
